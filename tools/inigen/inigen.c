#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <capstone/capstone.h>
#include "global.h"
#include "elf.h"
#include "util.h"

// Get constants from the repository
#include "constants/global.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/event_objects.h"

/*
 * ---------------------------------------------------------
 * Type definitions
 * ---------------------------------------------------------
 */

#define len(arr) (sizeof(arr)/sizeof(*arr))

//struct TMText {
//    int tmno;
//    int mapgp;
//    int mapno;
//    int scriptno;
//    int offset;
//    const char * text;
//};

struct TMText {
    int tmno;
    const char * label;
    const char * text;
};

struct StaticPokemon {
    const char * label;
    int offset;
};

static csh sCapstone;

static Elf32_Shdr * sh_text;

/*
 * ---------------------------------------------------------
 * Data
 * ---------------------------------------------------------
 */

static const char * gTypeNames[] = {
    "Normal",
    "Fighting",
    "Flying",
    "Poison",
    "Ground",
    "Rock",
    "Grass", // "Bug",
    "Ghost",
    "Steel",
    "Ghost", // "Mystery",
    "Fire",
    "Water",
    "Grass",
    "Electric",
    "Psychic",
    "Ice",
    "Dragon",
    "Dark"
};

const struct StaticPokemon gStaticPokemon[][8] = {
    {{ "CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall" , 3}, {"CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall", 6}, {"CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveeParty", 15}, {"CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveePC", 15}},
    {{"SaffronCity_Dojo_EventScript_HitmonleeBall", 12}, {"SaffronCity_Dojo_EventScript_HitmonleeBall", 19}},
    {{"SaffronCity_Dojo_EventScript_HitmonchanBall", 12}, {"SaffronCity_Dojo_EventScript_HitmonchanBall", 19}},
    {{"PowerPlant_EventScript_Electrode1", 17}, {"PowerPlant_EventScript_Electrode1", 24}},
    {{"PowerPlant_EventScript_Electrode2", 17}, {"PowerPlant_EventScript_Electrode2", 24}},
    {{"PowerPlant_EventScript_Zapdos", 20}, {"PowerPlant_EventScript_Zapdos", 27}, {"PowerPlant_EventScript_RanFromZapdos", 3}},
    {{"SeafoamIslands_B4F_EventScript_Articuno", 20}, {"SeafoamIslands_B4F_EventScript_Articuno", 27}, {"SeafoamIslands_B4F_EventScript_RanFromArticuno", 3}},
    {{"MtEmber_Summit_EventScript_Moltres", 20}, {"MtEmber_Summit_EventScript_Moltres", 27}, {"MtEmber_Summit_EventScript_RanFromMoltres", 3}},
    {{"CeruleanCave_B1F_EventScript_Mewtwo", 20}, {"CeruleanCave_B1F_EventScript_Mewtwo", 27}, {"CeruleanCave_B1F_EventScript_RanFromMewtwo", 3}},
    {{"Route12_EventScript_Snorlax", 53}, {"Route12_EventScript_Snorlax", 60}},
    {{"Route16_EventScript_Snorlax", 53}, {"Route16_EventScript_Snorlax", 60}},

};

const struct TMText gTMTexts[] = {

};

/*
 * ----------------------------------------------
 * Capstone callbacks
 * ----------------------------------------------
 */

static int IsLoadingStarterItems(const struct cs_insn * insn)
{
    static int to_return;
    Elf32_Sym *sym = GetSymbolByName("ScriptGiveMon");
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov r2, #0
    if (insn->id == ARM_INS_MOV
     && ops[0].type == ARM_OP_REG
     && ops[0].reg == ARM_REG_R2
     && ops[1].type == ARM_OP_IMM
     && ops[1].imm == 0)
        to_return = insn->address;
    // bl ScriptGiveMon
    else if (insn->id == ARM_INS_BL)
    {
        uint32_t target = ops[0].imm;
        if (target == (sym->st_value & ~1))
            return to_return;
    }
    return -1;
}

static int IsIntroLotadForCry_1(const struct cs_insn * insn)
{
    static int to_return;
    static unsigned tmp_reg, tmp_reg2;
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov rX, SPECIES_LOTAD / 2
    if (insn->id == ARM_INS_MOV
    && ops[0].type == ARM_OP_REG
    && ops[1].type == ARM_OP_IMM
    && ops[1].imm == SPECIES_LOTAD / 2)
    {
        to_return = insn->address;
        tmp_reg = ops[0].reg;
    }
    // lsl rX, rY, 1
    else if (insn->id == ARM_INS_LSL
    && ops[0].type == ARM_OP_REG
    && ops[1].type == ARM_OP_REG
    && ops[1].reg == tmp_reg
    && ops[2].type == ARM_OP_IMM
    && ops[2].imm == 1
    )
        tmp_reg2 = ops[0].reg;
    // str rX, [sp, 16]
    else if (insn->id == ARM_INS_STR
             && ops[0].type == ARM_OP_REG
             && ops[0].reg == tmp_reg2
             && ops[1].type == ARM_OP_MEM
             && !ops[1].subtracted
             && ops[1].mem.base == ARM_REG_SP
             && ops[1].mem.index == ARM_REG_INVALID
             && ops[1].mem.disp == 16)
        return to_return;

    return -1;
}

static int IsIntroLotadForCry_2(const struct cs_insn * insn)
{
    static int to_return;
    static unsigned tmp_reg;
    cs_arm_op * ops = insn->detail->arm.operands;
    // ldr rX, =SPECIES_LOTAD
    if (insn->id == ARM_INS_LDR
        && ops[0].type == ARM_OP_REG
        && ops[1].type == ARM_OP_MEM
        && !ops[1].subtracted
        && ops[1].mem.base == ARM_REG_PC
        && ops[1].mem.index == ARM_REG_INVALID)
    {
        to_return = (insn->address & ~3) + ops[1].mem.disp + 4;
        tmp_reg = ops[0].reg;
    }
    // str rX, [sp, #0x10]
    else if (insn->id == ARM_INS_STR
             && ops[0].type == ARM_OP_REG
             && ops[0].reg == tmp_reg
             && ops[1].type == ARM_OP_MEM
             && !ops[1].subtracted
             && ops[1].mem.base == ARM_REG_SP
             && ops[1].mem.index == ARM_REG_INVALID
             && ops[1].mem.disp == 16)
        return to_return;
    return -1;
}

static int IsIntroLotadForCry(const struct cs_insn * insn)
{
    int retval = IsIntroLotadForCry_1(insn);
    if (retval >= 0)
        return retval;
    return IsIntroLotadForCry_2(insn);
}

static int IsIntroLotadForPic_1(const struct cs_insn * insn)
{
    static int to_return;
    static unsigned tmp_reg;
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov rX, SPECIES_LOTAD / 2
    if (insn->id == ARM_INS_MOV
    && ops[0].type == ARM_OP_REG
    && ops[1].type == ARM_OP_IMM
    && ops[1].imm == SPECIES_LOTAD / 2)
    {
        to_return = insn->address;
        tmp_reg = ops[0].reg;
    }
    // lsl rX, rY, 1
    else if (insn->id == ARM_INS_LSL
    && ops[0].type == ARM_OP_REG
    && ops[1].type == ARM_OP_REG
    && ops[1].reg == tmp_reg
    && ops[2].type == ARM_OP_IMM
    && ops[2].imm == 1
    )
        return to_return;

    return -1;
}

static int IsIntroLotadForPic_2(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // ldr rX, =SPECIES_LOTAD
    if (insn->id == ARM_INS_LDR
        && ops[0].type == ARM_OP_REG
        && ops[1].type == ARM_OP_MEM
        && !ops[1].subtracted
        && ops[1].mem.base == ARM_REG_PC
        && ops[1].mem.index == ARM_REG_INVALID)
        return (insn->address & ~3) + ops[1].mem.disp + 4;
    return -1;
}

static int IsIntroLotadForPic(const struct cs_insn * insn)
{
    int retval = IsIntroLotadForPic_1(insn);
    if (retval >= 0)
        return retval;
    return IsIntroLotadForPic_2(insn);
}

static int IsRunIndoorsTweakOffset(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    if (insn->id == ARM_INS_AND
        && ops[0].type == ARM_OP_REG
        && ops[1].type == ARM_OP_REG
        && (insn - 1)->id == ARM_INS_MOV
        && (insn - 1)->detail->arm.operands[0].type == ARM_OP_REG
        && (insn - 1)->detail->arm.operands[1].type == ARM_OP_IMM
        && (insn - 1)->detail->arm.operands[0].reg == ops[0].reg
        && (insn - 1)->detail->arm.operands[1].imm == 4)
        return insn->address;
    return -1;
}

static int IsWallyZigzagoon_1(const struct cs_insn * insn)
{
    static int to_return;
    static unsigned tmp_reg;
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov rX, SPECIES_ZIGZAGOON / 2
    if (insn->id == ARM_INS_MOV
        && ops[0].type == ARM_OP_REG
        && ops[1].type == ARM_OP_IMM
        && ops[1].imm == SPECIES_ZIGZAGOON / 2)
    {
        to_return = insn->address;
        tmp_reg = ops[0].reg;
    }
        // lsl rX, rY, 1
    else if (insn->id == ARM_INS_LSL
             && ops[0].type == ARM_OP_REG
             && ops[0].reg == ARM_REG_R1
             && ops[1].type == ARM_OP_REG
             && ops[1].reg == tmp_reg
             && ops[2].type == ARM_OP_IMM
             && ops[2].imm == 1
        )
        return to_return;

    return -1;
}

static int IsWallyZigzagoon_2(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // ldr rX, =SPECIES_ZIGZAGOON
    if (insn->id == ARM_INS_LDR
        && ops[0].type == ARM_OP_REG
        && ops[0].reg == ARM_REG_R1
        && ops[1].type == ARM_OP_MEM
        && !ops[1].subtracted
        && ops[1].mem.base == ARM_REG_PC
        && ops[1].mem.index == ARM_REG_INVALID)
        return (insn->address & ~3) + ops[1].mem.disp + 4;
    return -1;
}

static int IsWallyZigzagoon(const struct cs_insn * insn)
{
    int retval = IsWallyZigzagoon_1(insn);
    if (retval >= 0)
        return retval;
    return IsWallyZigzagoon_2(insn);
}

static int IsWallyRalts_1(const struct cs_insn * insn)
{
    static int to_return;
    static unsigned tmp_reg;
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov rX, SPECIES_RALTS / 2
    if (insn->id == ARM_INS_MOV
        && ops[0].type == ARM_OP_REG
        && ops[1].type == ARM_OP_IMM
        && ops[1].imm == SPECIES_RALTS / 2)
    {
        to_return = insn->address;
        tmp_reg = ops[0].reg;
    }
        // lsl rX, rY, 1
    else if (insn->id == ARM_INS_LSL
             && ops[0].type == ARM_OP_REG
             && ops[0].reg == ARM_REG_R1
             && ops[1].type == ARM_OP_REG
             && ops[1].reg == tmp_reg
             && ops[2].type == ARM_OP_IMM
             && ops[2].imm == 1
        )
        return to_return;

    return -1;
}

static int IsWallyRalts_2(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // ldr rX, =SPECIES_RALTS
    if (insn->id == ARM_INS_LDR
        && ops[0].type == ARM_OP_REG
        && ops[0].reg == ARM_REG_R1
        && ops[1].type == ARM_OP_MEM
        && !ops[1].subtracted
        && ops[1].mem.base == ARM_REG_PC
        && ops[1].mem.index == ARM_REG_INVALID)
        return (insn->address & ~3) + ops[1].mem.disp + 4;
    return -1;
}

static int IsWallyRalts(const struct cs_insn * insn)
{
    int retval = IsWallyRalts_1(insn);
    if (retval >= 0)
        return retval;
    return IsWallyRalts_2(insn);
}

/*
 * ---------------------------------------------------------
 * get_instr_addr(
 *   FILE * elfFile,
 *   const char * symname,
 *   int (*callback)(const struct cs_insn *)
 * )
 *
 * Disassembles the function of the provided name until the
 * callback returns a positive integer, then returns that
 * integer. If the end of the function is reached and the
 * callback never returns positive, -1 is returned instead.
 * The callback takes a single argument, a pointer to a
 * disassembled instruction. It then runs internal logic to
 * determine whether the instruction or sequence of in-
 * structions is what is desired, then returns the address
 * of that instruction.
 * ---------------------------------------------------------
 */

static int get_instr_addr(FILE * elfFile, const char * symname, int (*callback)(const struct cs_insn *))
{
    int retval = -1;
    Elf32_Sym * sym = GetSymbolByName(symname);
    fseek(elfFile, (sym->st_value & ~1) - sh_text->sh_addr + sh_text->sh_offset, SEEK_SET);
    unsigned char * data = malloc(sym->st_size);
    if (fread(data, 1, sym->st_size, elfFile) != sym->st_size)
        FATAL_ERROR("fread");
    struct cs_insn *insn;
    int count = cs_disasm(sCapstone, data, sym->st_size, sym->st_value & ~1, 0, &insn);
    for (int i = 0; i < count; i++) {
        int to_return = callback(&insn[i]);
        if (to_return >= 0) {
            retval = to_return;
            break;
        }
    }
    cs_free(insn, count);
    free(data);
    return retval;
}

int main(int argc, char ** argv)
{
    const char * romName = "Emerald (U)";
    const char * romCode = "BPEE";
    FILE * elfFile = NULL;
    FILE * outFile = NULL;

    // Argument parser
    for (int i = 1; i < argc; i++) {
        char * arg = argv[i];
        if (strcmp(arg, "--name") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --name\n");
            }
            romName = argv[i];
        } else if (strcmp(arg, "--code") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --code\n");
            }
            romCode = argv[i];
        } else if (arg[0] == '-') {
            FATAL_ERROR("unrecognized option: \"%s\"\n", arg);
        } else if (elfFile == NULL) {
            elfFile = fopen(arg, "rb");
            if (elfFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for reading\n", arg);
            }
        } else if (outFile == NULL) {
            outFile = fopen(arg, "w");
            if (outFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for writing\n", arg);
            }
        } else {
            FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
        }
    }

    if (outFile == NULL) {
        FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
    }

    // Load the ELF metadata
    InitElf(elfFile);
#ifdef _MSC_VER
#define print(format, ...) (fprintf(outFile, format, __VA_ARGS__))
#else
#define print(format, ...) (fprintf(outFile, format, ##__VA_ARGS__))
#endif
#define config_set(name, value) (print("%s=0x%X\n", (name), (value)))
#define sym_get(name) (GetSymbolByName((name))->st_value)
#define config_sym(name, symname) (config_set((name), sym_get(symname) & 0xFFFFFF))

    // Initialize Capstone
    cs_open(CS_ARCH_ARM, CS_MODE_THUMB, &sCapstone);
    cs_option(sCapstone, CS_OPT_DETAIL, CS_OPT_ON);
    sh_text = GetSectionHeaderByName(".text");

    // Start writing the INI
    print("[%s]\n", romName);
    print("Game=%s\n", romCode);
    print("Version=0\n");
    print("Type=Em\n");
    print("TableFile=gba_english\n");

    // Find the first block after the ROM
    int shnum = GetSectionHeaderCount();
    uint32_t entry = GetEntryPoint();
    uint32_t end = entry;
    for (int i = 0; i < shnum; i++) {
        Elf32_Shdr * sec = GetSectionHeader(i);
        end = max(end, sec->sh_addr + sec->sh_size);
    }
    end -= entry;
    if (end & 0xFFFF) {
        end += 0x10000 - (end & 0xFFFF);
    }
    print("FreeSpace=0x%X\n", end);
//
//    // Pokemon data
//    print("PokemonCount=%d\n", NUM_SPECIES - 1);
//    print("PokemonNameLength=%d\n", POKEMON_NAME_LENGTH + 1);
//    config_sym("PokemonMovesets", "gLevelUpLearnsets");
//    config_sym("PokemonTMHMCompat", "gTMHMLearnsets");
//    config_sym("PokemonEvolutions", "gEvolutionTable");
//    config_sym("StarterPokemon", "sStarterMon");
//    // This symbol is inside a C function, so we must take an assist from capstone.
//    config_set("StarterItems", get_instr_addr(elfFile, "CB2_GiveStarter", IsLoadingStarterItems) & 0xFFFFFF);
//    config_sym("TrainerData", "gTrainers");
//    Elf32_Sym * Em_gTrainers = GetSymbolByName("gTrainers");
//    config_sym("WildPokemon", "gWildMonHeaders");
//    print("TrainerEntrySize=%d\n", Em_gTrainers->st_size / TRAINERS_COUNT);
//    config_set("TrainerCount", TRAINERS_COUNT);
//    config_sym("TrainerClassNames", "gTrainerClassNames");
//    Elf32_Sym * Em_gTrainerClassNames = GetSymbolByName("gTrainerClassNames");
//    print("TrainerClassCount=%d\n", TRAINER_CLASS_COUNT);
//    print("TrainerClassNameLength=%d\n", Em_gTrainerClassNames->st_size / TRAINER_CLASS_COUNT);
//    print("TrainerNameLength=%d\n", 12); // hardcoded for now
//    print("DoublesTrainerClasses=[%d, %d, %d, %d, %d]\n", TRAINER_CLASS_SR_AND_JR, TRAINER_CLASS_TWINS, TRAINER_CLASS_YOUNG_COUPLE, TRAINER_CLASS_OLD_COUPLE, TRAINER_CLASS_SIS_AND_BRO); // hardcoded for now
//    Elf32_Sym * Em_gItems = GetSymbolByName("gItems");
//    print("ItemEntrySize=%d\n", Em_gItems->st_size / ITEMS_COUNT);
//    print("ItemCount=%d\n", ITEMS_COUNT - 2); // NONE, DONE_BUTTON
//    print("MoveCount=%d\n", MOVES_COUNT - 1);
//    config_sym("MoveDescriptions", "gMoveDescriptionPointers");
//    Elf32_Sym * Em_gMoveNames = GetSymbolByName("gMoveNames");
//    print("MoveNameLength=%d\n", Em_gMoveNames->st_size / MOVES_COUNT);
//    Elf32_Sym * Em_gAbilityNames = GetSymbolByName("gAbilityNames");
//    print("AbilityNameLength=%d\n", Em_gAbilityNames->st_size / ABILITIES_COUNT);
//    config_sym("TmMoves", "sTMHMMoves");
//    config_sym("TmMovesDuplicate", "sUnused_StatStrings");
//    config_sym("MoveTutorData", "gTutorMoves");
//    Elf32_Sym* Em_gTutorMoves = GetSymbolByName("gTutorMoves");
//    print("MoveTutorMoves=%d\n", Em_gTutorMoves->st_size / 2);
//    config_sym("ItemImages", "gItemIconTable");
//
//    print("TmPals=[");
//    char buffer[64];
//    for (int i = 0; i < len(gTypeNames); i++) {
//        sprintf(buffer, "gItemIconPalette_%sTMHM", gTypeNames[i]);
//        if (i != 0)
//            print(",");
//        print("0x%X", GetSymbolByName(buffer)->st_value & 0xFFFFFF);
//    }
//    print("]\n");
//
//    config_set("IntroCryOffset", get_instr_addr(elfFile, "Task_NewGameBirchSpeechSub_InitPokeBall", IsIntroLotadForCry) & 0xFFFFFF);
//    config_set("IntroSpriteOffset", get_instr_addr(elfFile, "NewGameBirchSpeech_CreateLotadSprite", IsIntroLotadForPic) & 0xFFFFFF);
//    print("ItemBallPic=%d\n", OBJ_EVENT_GFX_ITEM_BALL);
//    config_sym("TradeTableOffset", "sIngameTrades");
//    Elf32_Sym * Em_gIngameTrades = GetSymbolByName("sIngameTrades");
//    print("TradeTableSize=%d\n", Em_gIngameTrades->st_size / 60); // hardcoded for now
//    print("TradesUnused=[]\n"); // so randomizer doesn't complain
//    config_set("CatchingTutorialOpponentMonOffset", get_instr_addr(elfFile, "StartWallyTutorialBattle", IsWallyRalts) & 0xFFFFFF);
//    config_set("CatchingTutorialPlayerMonOffset", get_instr_addr(elfFile, "PutZigzagoonInPlayerParty", IsWallyZigzagoon) & 0xFFFFFF);
//    config_sym("PCPotionOffset", "gNewGamePCItems");
//
//    // These may need some fixing to support dynamic offsets.
//    print("StaticPokemonSupport=1\n");
//    for (int i = 0; i < len(gStaticPokemon); i++) {
//        print("StaticPokemon[]=[");
//        for (int j = 0; j < 8; j++) {
//            if (gStaticPokemon[i][j].label == NULL) break;
//            if (j != 0)
//                print(",");
//            print("0x%X", (sym_get(gStaticPokemon[i][j].label) & 0xFFFFFF) + gStaticPokemon[i][j].offset);
//        }
//        print("]\n");
//    }
//    for (int i = 0; i < len(gTMTexts); i++) {
//        Elf32_Sym * sym = GetSymbolByName(gTMTexts[i].label);
//        print("TMTextSpdc[]=[%d,0x%X,%s]\n", gTMTexts[i].tmno, (sym->st_value + 2) & 0xFFFFFF, gTMTexts[i].text);
//    }
//    for (int i = 0; i < len(gMoveTutorTexts); i++) {
//        Elf32_Sym * sym = GetSymbolByName(gMoveTutorTexts[i].label);
//        print("MoveTutorTextSpdc[]=[%d,0x%X,%s]\n", gMoveTutorTexts[i].tmno, (sym->st_value + 2) & 0xFFFFFF, gMoveTutorTexts[i].text);
//    }
//
//    config_sym("PokedexOrder", "gSpeciesToNationalPokedexNum");
//    config_sym("CheckValueOffset", "gRandomizerCheckValue");

    DestroyResources();
    fclose(outFile);
    fclose(elfFile);
    return 0;
}
