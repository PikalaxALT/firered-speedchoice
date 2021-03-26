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

const struct
{
    uint16_t vanilla;
    struct StaticPokemon mons[4];
} gStaticPokemon[] = {
    {SPECIES_EEVEE, {{ "CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall" , 5}, {"CeladonCity_Condominiums_RoofRoom_EventScript_EeveeBall", 8}, {"CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveeParty", 15}, {"CeladonCity_Condominiums_RoofRoom_EventScript_GetEeveePC", 15}}},
    {SPECIES_HITMONLEE, {{"SaffronCity_Dojo_EventScript_HitmonleeBall", 12}, {"SaffronCity_Dojo_EventScript_HitmonleeBall", 19}}},
    {SPECIES_HITMONCHAN, {{"SaffronCity_Dojo_EventScript_HitmonchanBall", 12}, {"SaffronCity_Dojo_EventScript_HitmonchanBall", 19}}},
    {SPECIES_ELECTRODE, {{"PowerPlant_EventScript_Electrode1", 17}, {"PowerPlant_EventScript_Electrode1", 24}}},
    {SPECIES_ELECTRODE, {{"PowerPlant_EventScript_Electrode2", 17}, {"PowerPlant_EventScript_Electrode2", 24}}},
    {SPECIES_ZAPDOS, {{"PowerPlant_EventScript_Zapdos", 20}, {"PowerPlant_EventScript_Zapdos", 27}, {"PowerPlant_EventScript_RanFromZapdos", 3}}},
    {SPECIES_ARTICUNO, {{"SeafoamIslands_B4F_EventScript_Articuno", 20}, {"SeafoamIslands_B4F_EventScript_Articuno", 27}, {"SeafoamIslands_B4F_EventScript_RanFromArticuno", 3}}},
    {SPECIES_MOLTRES, {{"MtEmber_Summit_EventScript_Moltres", 20}, {"MtEmber_Summit_EventScript_Moltres", 27}, {"MtEmber_Summit_EventScript_RanFromMoltres", 3}}},
    {SPECIES_MEWTWO, {{"CeruleanCave_B1F_EventScript_Mewtwo", 21}, {"CeruleanCave_B1F_EventScript_Mewtwo", 41}, {"CeruleanCave_B1F_EventScript_RanFromMewtwo", 3}}},
    {SPECIES_SNORLAX, {{"Route12_EventScript_Snorlax", 53}, {"Route12_EventScript_Snorlax", 60}}},
    {SPECIES_SNORLAX, {{"Route16_EventScript_Snorlax", 53}, {"Route16_EventScript_Snorlax", 60}}},
    {SPECIES_HYPNO, {{"ThreeIsland_BerryForest_EventScript_Lostelle", 57}, {"ThreeIsland_BerryForest_EventScript_Lostelle", 63}}},
    {SPECIES_DEOXYS, {{"BirthIsland_Exterior_EventScript_Deoxys", 38}, {"BirthIsland_Exterior_EventScript_Deoxys", 54}, {"BirthIsland_Exterior_EventScript_DefeatedDeoxys", 6}, {"BirthIsland_Exterior_EventScript_RanFromDeoxys", 3}}},
    {SPECIES_HO_OH, {{"NavelRock_Summit_EventScript_HoOh", 65}, {"NavelRock_Summit_EventScript_HoOh", 112}, {"NavelRock_Summit_EventScript_DefeatedHoOh", 6}, {"NavelRock_Summit_EventScript_RanFromHoOh", 3}}},
    {SPECIES_LUGIA, {{"NavelRock_Base_EventScript_Lugia", 86}, {"NavelRock_Base_EventScript_Lugia", 97}, {"NavelRock_Base_EventScript_DefeatedLugia", 6}, {"NavelRock_Base_EventScript_RanFromLugia", 3}}},
    {SPECIES_AERODACTYL, {{"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveAerodactyl", 3}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveAerodactyl", 7}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveAerodactyl", 18}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowOldAmber", 2}}},
    {SPECIES_OMANYTE, {{"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveOmanyte", 3}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveOmanyte", 7}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveOmanyte", 18}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowHelixFossil", 2}}},
    {SPECIES_KABUTO, {{"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveKabuto", 3}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveKabuto", 7}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_GiveKabuto", 18}, {"CinnabarIsland_PokemonLab_ExperimentRoom_EventScript_ShowDomeFossil", 2}}},
    {SPECIES_LAPRAS, {{"SilphCo_7F_EventScript_LaprasGuy", 25}, {"SilphCo_7F_EventScript_ReceiveLaprasParty", 14}, {"SilphCo_7F_EventScript_ReceiveLaprasPC", 14}}},
    {SPECIES_MAGIKARP, {{"Route4_PokemonCenter_1F_EventScript_TryBuyMagikarp", 36}, {"Route4_PokemonCenter_1F_EventScript_PayForMagikarp", 22}}},
    {SPECIES_ABRA, {{"CeladonCity_GameCorner_PrizeRoom_EventScript_Abra", 3}, {"CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon", 47}}},
    {SPECIES_CLEFAIRY, {{"CeladonCity_GameCorner_PrizeRoom_EventScript_Clefairy", 3}, {"CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon", 58}}},
    {SPECIES_DRATINI, {{"CeladonCity_GameCorner_PrizeRoom_EventScript_DratiniPinsir", 3}, {"CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon", 69}}},
    {SPECIES_SCYTHER, {{"CeladonCity_GameCorner_PrizeRoom_EventScript_ScytherDratini", 3}, {"CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon", 80}}},
    {SPECIES_PORYGON, {{"CeladonCity_GameCorner_PrizeRoom_EventScript_Porygon", 3}, {"CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon", 91}}},
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
    print("Type=FRLG\n");
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
    // These may need some fixing to support dynamic offsets.
    print("StaticPokemonSupport=1\n");
    for (int i = 0; i < len(gStaticPokemon); i++) {
        print("StaticPokemon[]=[");
        for (int j = 0; j < 4; j++) {
            if (gStaticPokemon[i].mons[j].label == NULL) break;
            if (j != 0)
                print(",");
            Elf32_Sym * sym = GetSymbolByName(gStaticPokemon[i].mons[j].label);
            if (sym != NULL) {
                Elf32_Shdr * shdr = GetSectionHeader(sym->st_shndx);
                uint32_t offs = sym->st_value + gStaticPokemon[i].mons[j].offset;
                fseek(elfFile, offs - shdr->sh_addr + shdr->sh_offset, SEEK_SET);
                uint16_t species;
                fread(&species, 2, 1, elfFile);
                if (species != gStaticPokemon[i].vanilla) {
                    FATAL_ERROR("Static Pokémon %d entry %d: Expected 0x%X, got 0x%X\n", i, j, gStaticPokemon[i].vanilla, species);
                }
                print("0x%X", offs & 0xFFFFFF);
            } else {
                FATAL_ERROR("Static Pokemon %d entry %d: Symbol \"%s\" not found\n", i, j, gStaticPokemon[i].mons[j].label);
            }
        }
        print("]\n");
    }
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
