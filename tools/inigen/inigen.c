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
#include "constants/trainer_classes.h"
#include "constants/maps.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/event_objects.h"
#include "constants/speedchoice.h"

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

struct PlotlessKeyItem {
    uint16_t vanillaItem;
    const char * label;
    int offset;
};

static csh sCapstone;

static Elf32_Shdr * sh_text;
static Elf32_Shdr * sh_rodata;
static Elf32_Shdr * sh_scripts;

/*
 * ---------------------------------------------------------
 * Data
 * ---------------------------------------------------------
 */

static const char * gTypeNames[] = {
    "normal",
    "fighting",
    "flying",
    "poison",
    "ground",
    "rock",
    "grass", // "Bug",
    "ghost",
    "steel",
    "ghost", // "Mystery",
    "fire",
    "water",
    "grass",
    "electric",
    "psychic",
    "ice",
    "dragon",
    "dark"
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
    { 3, "CeruleanCity_Gym_Text_ExplainTM03", "TM03 teaches [move].\\pUse it on a worthy POKéMON!"},
    { 4, "SaffronCity_Gym_Text_ExplainTM04", "TM04 is [move]."},
    { 6, "FuchsiaCity_Gym_Text_KogaExplainTM06", "Sealed within that TM06 lies [move]!\\pIt is a secret technique dating back some four hundred years."},
    {16, "CeladonCity_DepartmentStore_Roof_Text_ExplainTM16", "TM16 contains [move]."},
    {19, "CeladonCity_Gym_Text_ExplainTM19", "TM19 contains [move].\\pWouldn’t you agree that it’s a wonderful move?"},
    {20, "CeladonCity_DepartmentStore_Roof_Text_ExplainTM20", "TM20 contains [move]."},
    {26, "ViridianCity_Gym_Text_ExplainTM26", "TM26 contains [move].\\pIt is a powerful technique.\\pI made it when I ran the GYM here, far too long ago…"},
    {27, "Route12_NorthEntrance_2F_Text_ExplainTM27", "TM27 is a move called [move]…\\pIf you treat your POKéMON good, it will return your love by working its hardest in battle."},
    {28, "CeruleanCity_House2_Text_RocketsStoleTMForDig", "Those miserable ROCKETS!\\pLook what they’ve done to my house!\\pThey stole a TM for teaching POKéMON how to [move]!\\pThat cost me a bundle, it did!"},
    {28, "CeruleanCity_House2_Text_TeachDiglettDigWithoutTM", "I figure what’s lost is lost.\\pI decided to catch a POKéMON that could [move] without a TM."},
    {29, "SaffronCity_MrPsychicsHouse_Text_ExplainTM29", "You already know, don’t you? TM29 is [move]."},
    {33, "CeladonCity_DepartmentStore_Roof_Text_ExplainTM33", "TM33 contains [move]."},
    {34, "VermilionCity_Gym_Text_ExplainTM34", "TM34 contains [move]!\\pTeach it to your favorite POKéMON!"},
    {38, "CinnabarIsland_Gym_Text_BlainePostBattle", "TM38 contains [move].\\nTeach it to strong POKéMON."},
    {38, "CinnabarIsland_Gym_Text_FireBlastIsUltimateFireMove", "[move] is the ultimate\\ntechnique.\\pDon't waste it on weak POKéMON."},
    {39, "PewterCity_Gym_Text_ExplainTM39", "A TM, Technical Machine, contains a technique for POKéMON.\\pUsing a TM teaches the move it contains to a POKéMON.\\pA TM is good for only one use.\\pSo, when you use one, pick the POKéMON carefully.\\pAnyways… TM39 contains [move]."},
};

const struct TMText gMoveTutorTexts[] = {
    { 0, "Text_MegaPunchTeach", "A hit of roaring ferocity!\\pPacked with destructive power!\\pWhen the chips are down, [move] is the ultimate attack! You agree, yes?\\pNow! Let me teach it to your POKéMON!"},
    { 0, "Text_MegaPunchTaught", "Now, we are comrades in the way of [move]!\\pYou should go before you’re seen by the misguided fool who trains only silly moves over there."},
    { 0, "Text_MegaPunchDeclined", "You’ll be back when you understand the worth of [move]."},
    { 1, "Text_SwordsDanceTeach", "Not many people come out here.\\pIf I train here, I’m convinced that I’ll get stronger and stronger.\\pYep, stronger and stronger…\\pHow would you like to learn a strong move? It’s [move]."},
    { 2, "Text_MegaKickTeach", "A hit of brutal ferocity!\\pPacked with destructive power!\\pWhen you get right down to it, [move] is the ultimate attack! Don’t you agree?\\pOkay! I’ll teach it to your POKéMON!"},
    { 2, "Text_MegaKickTaught", "Now, we are soul mates in the way of [move]!\\pYou should run before you’re seen by the deluded nitwit who trains only simple moves over there."},
    { 2, "Text_MegaKickDeclined", "You’ll come crawling back when you realize the value of [move]."},
    { 3, "Text_BodySlamTeach", "Ready? Boing!\\pWe’re having a wrestling match to see who wimps out first.\\pIf you were to join us, you’d be squashed like a bug, though…\\pHow about I teach [move] to a POKéMON of yours instead?"},
    { 3, "Text_BodySlamWhichMon", "Which POKéMON wants to learn how to [move]?"},
    { 4, "Text_DoubleEdgeTeach", "You should be proud of yourself, having battled your way through VICTORY ROAD so courageously.\\pIn recognition of your feat, I’ll teach you [move].\\pWould you like me to teach that technique?"},
    { 4, "Text_DoubleEdgeWhichMon", "Which POKéMON should I teach [move]?"},
    { 5, "Text_CounterTeach", "Oh, hi! I finally finished POKéMON.\\pNot done yet? How about I teach you a good move?\\pThe move I have in mind is [move]."},
    { 5, "Text_CounterWhichMon", "Which POKéMON should I teach [move] to?"},
    { 5, "Text_CounterTaught", "Are you using that [move] move I taught your POKéMON?"},
    { 6, "Text_SeismicTossTeach", "The secrets of space… The mysteries of earth…\\pThere are so many things about which we know so little.\\pBut that should spur us to study harder, not toss in the towel.\\pThe only thing you should toss…\\pWell, how about [move]? Should I teach that to a POKéMON?"},
    { 6, "Text_SeismicTossWhichMon", "Which POKéMON wants to learn [move]?"},
    { 7, "Text_MimicTeach", "Oh wow! A POKé DOLL!\\pFor me? Thank you!\\pYou know what? I can teach the move [move]."},
    { 7, "Text_MimicWhichMon", "I really love [move]! Who’s going to learn it?"},
    { 7, "Text_MimicDeclined", "Don’t you like [move]?"},
    { 8, "Text_MetronomeTeach", "Tch-tch-tch! I’ll teach you a nifty move.\\pTeach it to a POKéMON, and watch the fun unfold!\\pIt’s a move called [move]. Does it strike your fancy?"},
    { 8, "Text_MetronomeTaught", "Tch-tch-tch! That’s the sound of a metronome.\\pIt inspired me to start teaching [move] to interested trainers."},
    { 9, "Text_SoftboiledTeach", "Hello, there!\\pI’ve seen you about, but I never had a chance to chat.\\pIt must be good luck that brought us together finally.\\pI’d like to celebrate by teaching you the move [move]."},
    { 9, "Text_SoftboiledWhichMon", "So, who’s the POKéMON that gets the chance to learn [move]?"},
    {10, "Text_DreamEaterTeach", "Yawn! I must have dozed off in the sun.\\pI had this weird dream about a DROWZEE eating my dream.\\pAnd… I learned how to teach [move]…\\pOogh, this is too spooky!\\pLet me teach it to a POKéMON so I can forget about it!"},
    {10, "Text_DreamEaterWhichMon", "Which POKéMON wants to learn [move]?"},
    {11, "Text_ThunderWaveTeach", "Eeek! No! Stop! Help!\\pOh, you’re not with TEAM ROCKET. I’m sorry, I thought…\\pWill you forgive me if I teach you the [move] technique?"},
    {11, "Text_ThunderWaveWhichMon", "Which POKéMON should I teach [move]?"},
    {11, "Text_ThunderWaveTaught", "[move] is a useful move, but it might not work on some POKéMON."},
    {11, "Text_ThunderWaveDeclined", "Oh… But [move] is convenient…"},
    {12, "Text_ExplosionTeach", "Can you imagine? If this volcano were to erupt?\\pThe explosion would be the end of us. How terrifying is that?\\pWhile we’re terrified, would you like me to teach [move]?"},
    {12, "Text_ExplosionWhichMon", "You’re terribly brave!\\pWhich POKéMON should I teach [move]?"},
    {12, "Text_ExplosionTaught", "Using [move] while on this volcano…\\pWhat a terrifying thrill!"},
    {13, "Text_RockSlideTeach", "When you’re up on a rocky mountain like this, rockslides are a threat.\\pCan you imagine? Boulders tumbling down on you?\\pThat’d be, like, waaaaaaaaaaah! Total terror!\\pYou don’t seem to be scared. Want to try using [move]?"},
    {13, "Text_RockSlideWhichMon", "Which POKéMON should I teach [move]?"},
    {14, "Text_SubstituteTeach", "Aww, I wish I was a KANGASKHAN baby.\\pI’d love to be a substitute for the baby…\\pAnd snuggle in the mother KANGASKHAN’s belly pouch.\\pBut only POKéMON can do that…\\pOn an unrelated note, want me to teach [move] to one of your POKéMON?"},
    {14, "Text_SubstituteWhichMon", "Which POKéMON wants to learn [move]?"},
    {14, "Text_SubstituteDeclined", "Oh, really? [move] seems so fun…"},
};

struct PlotlessKeyItem gKeyItems[] = {
    { ITEM_BICYCLE, "CeruleanCity_BikeShop_EventScript_RandomizedItem", 1 },
    { ITEM_SILPH_SCOPE, "RocketHideout_B4F_EventScript_RandoSilphScope", 3 },
    { ITEM_LIFT_KEY, "RocketHideout_B4F_EventScript_RandoLiftKey", 3 },
    { ITEM_CARD_KEY, "SilphCo_5F_EventScript_ItemCardKey_Rando", 3 }
};

/*
 * ----------------------------------------------
 * Capstone callbacks
 * ----------------------------------------------
 */

static int IsIntroNidoranF(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov r0, SPECIES_NIDORAN_F
    if (insn->id == ARM_INS_MOV
    && ops[0].type == ARM_OP_REG
    && ops[0].reg == ARM_REG_R0
    && ops[1].type == ARM_OP_IMM
    && ops[1].imm == SPECIES_NIDORAN_F)
    {
        return insn->address;
    }

    return -1;
}

static int IsIntroNidoranF2(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov r0, SPECIES_NIDORAN_F
    if (insn->id == ARM_INS_MOV
    && ops[0].type == ARM_OP_REG
    && ops[0].reg == ARM_REG_R2
    && ops[1].type == ARM_OP_IMM
    && ops[1].imm == SPECIES_NIDORAN_F)
    {
        return insn->address;
    }

    return -1;
}

static int IsOldManWeedle(const struct cs_insn * insn)
{
    cs_arm_op * ops = insn->detail->arm.operands;
    // mov r1, SPECIES_WEEDLE
    if (insn->id == ARM_INS_MOV
        && ops[0].type == ARM_OP_REG
        && ops[0].reg == ARM_REG_R1
        && ops[1].type == ARM_OP_IMM
        && ops[1].imm == SPECIES_WEEDLE)
    {
        return insn->address;
    }

    return -1;
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
#define sym_get(name) ({Elf32_Sym * sym = GetSymbolByName((name)); if (sym == NULL) {FATAL_ERROR("Failed to get symbol named %s\n", (name));} sym->st_value;})
#define config_sym(name, symname) (config_set((name), sym_get(symname) & 0xFFFFFF))

    // Initialize Capstone
    cs_open(CS_ARCH_ARM, CS_MODE_THUMB, &sCapstone);
    cs_option(sCapstone, CS_OPT_DETAIL, CS_OPT_ON);
    sh_text = GetSectionHeaderByName(".text");
    sh_rodata = GetSectionHeaderByName(".rodata");
    sh_scripts = GetSectionHeaderByName("script_data");

    // Start writing the INI
    print("[%s]\n", romName);
    print("Game=%s\n", romCode);
    print("Version=%s\n", SPEEDCHOICE_VERSION);
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
    print("FreeSpace=0x%X\n", 0x01000000 - end);

    // Pokemon data
    print("PokemonCount=%d\n", NUM_SPECIES - 1);
    print("PokemonNameLength=%d\n", POKEMON_NAME_LENGTH + 1);
    config_sym("PokemonMovesets", "gLevelUpLearnsets");
    config_sym("PokemonTMHMCompat", "sTMHMLearnsets");
    config_sym("PokemonEvolutions", "gEvolutionTable");
    print("StarterPokemon=0x%X\n", (sym_get("PalletTown_ProfessorOaksLab_EventScript_BulbasaurBall") + 10) & 0xFFFFFF);
    Elf32_Sym * Fr_gTrainers = GetSymbolByName("gTrainers");
    print("TrainerData=0x%X\n", Fr_gTrainers->st_value & 0xFFFFFF);
    print("TrainerEntrySize=%d\n", Fr_gTrainers->st_size / NUM_TRAINERS);
    config_set("TrainerCount", NUM_TRAINERS);
    Elf32_Sym * Fr_gTrainerClassNames = GetSymbolByName("gTrainerClassNames");
    print("TrainerClassNames=0x%X\n", Fr_gTrainerClassNames->st_value & 0xFFFFFF);
    print("TrainerClassCount=%d\n", TRAINER_CLASS_COUNT);
    print("TrainerClassNameLength=%d\n", Fr_gTrainerClassNames->st_size / TRAINER_CLASS_COUNT);
    print("TrainerNameLength=%d\n", 12); // hardcoded for now
    print("DoublesTrainerClasses=[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",
          CLASS_SR_AND_JR, CLASS_TWINS, CLASS_YOUNG_COUPLE, CLASS_OLD_COUPLE, CLASS_SIS_AND_BRO, // RS
          CLASS_TWINS_2, CLASS_COOL_COUPLE, CLASS_YOUNG_COUPLE_2, CLASS_CRUSH_KIN, CLASS_SIS_AND_BRO_2 // FRLG
      ); // hardcoded for now
    Elf32_Sym * Fr_gItems = GetSymbolByName("gItems");
    print("ItemEntrySize=%d\n", Fr_gItems->st_size / ITEMS_COUNT);
    print("ItemCount=%d\n", ITEMS_COUNT - 2); // NONE, DONE_BUTTON
    print("MoveCount=%d\n", MOVES_COUNT - 1);
    config_sym("MoveDescriptions", "gMoveDescriptionPointers");
    Elf32_Sym * Fr_gMoveNames = GetSymbolByName("gMoveNames");
    print("MoveNameLength=%d\n", Fr_gMoveNames->st_size / MOVES_COUNT);
    Elf32_Sym * Fr_gAbilityNames = GetSymbolByName("gAbilityNames");
    print("AbilityNameLength=%d\n", Fr_gAbilityNames->st_size / ABILITIES_COUNT);
    config_sym("TmMoves", "sTMHMMoves");
    config_sym("TmMovesDuplicate", "sTMHMMoves_Duplicate");
    Elf32_Sym* Fr_gTutorMoves = GetSymbolByName("sTutorMoves");
    print("MoveTutorData=0x%X\n", Fr_gTutorMoves->st_value & 0xFFFFFF);
    print("MoveTutorMoves=%d\n", Fr_gTutorMoves->st_size / 2);
    config_sym("ItemImages", "sItemIconGfxPtrs");

    print("TmPals=[");
    char buffer[256];
    for (int i = 0; i < len(gTypeNames); i++) {
        sprintf(buffer, "gFile_graphics_items_icon_palettes_%s_tm_hm_palette", gTypeNames[i]);
        if (i != 0)
            print(",");
        print("0x%X", GetSymbolByName(buffer)->st_value & 0xFFFFFF);
    }
    print("]\n");

    config_set("IntroCryOffset", get_instr_addr(elfFile, "Task_OakSpeech13", IsIntroNidoranF) & 0xFFFFFF);
    config_set("IntroSpriteOffset", get_instr_addr(elfFile, "CreateNidoranFSprite", IsIntroNidoranF) & 0xFFFFFF);
    config_set("IntroOtherOffset", get_instr_addr(elfFile, "CreateNidoranFSprite", IsIntroNidoranF2) & 0xFFFFFF);
    print("ItemBallPic=%d\n", OBJ_EVENT_GFX_ITEM_BALL);
    Elf32_Sym * Fr_gIngameTrades = GetSymbolByName("sInGameTrades");
    print("TradeTableOffset=0x%X\n", Fr_gIngameTrades->st_value & 0xFFFFFF);
    print("TradeTableSize=%d\n", Fr_gIngameTrades->st_size / 60); // hardcoded for now
    print("TradesUnused=[]\n"); // so randomizer doesn't complain
    config_set("CatchingTutorialOpponentMonOffset", get_instr_addr(elfFile, "StartOldManTutorialBattle", IsOldManWeedle) & 0xFFFFFF);
    config_sym("PCPotionOffset", "gNewGamePCItems");

    Elf32_Sym * Fr_gWildMonHeaders = GetSymbolByName("gWildMonHeaders");
    print("WildPokemon=0x%X\n", Fr_gWildMonHeaders->st_value & 0xFFFFFF);
    print("BattleTrappersBanned=[");
    bool foundTrapBannedMap = false;
    int encno = 0;
    fseek(elfFile, Fr_gWildMonHeaders->st_value - sh_rodata->sh_addr + sh_rodata->sh_offset, SEEK_SET);
    for (int i = 0; i < Fr_gWildMonHeaders->st_size / 20; i++) {
        uint8_t mapGroup;
        uint8_t mapNum;
        uint32_t encGroups[4];
        if (!fread(&mapGroup, 1, 1, elfFile))
            FATAL_ERROR("fread");
        if (!fread(&mapNum, 1, 1, elfFile))
            FATAL_ERROR("fread");
        fseek(elfFile, 2, SEEK_CUR);
        if (!fread(encGroups, 4, 4, elfFile))
            FATAL_ERROR("fread");
        for (int j = 0; j < 4; j++) {
            if (encGroups[j] != 0) {
                if (mapGroup == MAP_GROUP(POKEMON_TOWER_3F) && mapNum >= MAP_NUM(POKEMON_TOWER_3F) && mapNum <= MAP_NUM(POKEMON_TOWER_7F)) {
                    if (foundTrapBannedMap) print(",");
                    print("%d", encno);
                    foundTrapBannedMap = true;
                }
                encno++;
            }
        }
    }
    print("]\n");
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
                uint32_t offs = sym->st_value + gStaticPokemon[i].mons[j].offset;
                fseek(elfFile, offs - sh_scripts->sh_addr + sh_scripts->sh_offset, SEEK_SET);
                uint16_t species;
                if (!fread(&species, 2, 1, elfFile))
                    FATAL_ERROR("fread");
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
    for (int i = 0; i < len(gTMTexts); i++) {
        Elf32_Sym * sym = GetSymbolByName(gTMTexts[i].label);
        print("TMTextSpdc[]=[%d,0x%X,%s]\n", gTMTexts[i].tmno, (sym->st_value) & 0xFFFFFF, gTMTexts[i].text);
    }
    for (int i = 0; i < len(gMoveTutorTexts); i++) {
        Elf32_Sym * sym = GetSymbolByName(gMoveTutorTexts[i].label);
        print("MoveTutorTextSpdc[]=[%d,0x%X,%s]\n", gMoveTutorTexts[i].tmno, (sym->st_value) & 0xFFFFFF, gMoveTutorTexts[i].text);
    }

    for (int i = 0; i < len(gKeyItems); i++) {
        Elf32_Sym * sym = GetSymbolByName(gKeyItems[i].label);
        if (sym == NULL)
            FATAL_ERROR("Unable to find symbol \"%s\"\n", gKeyItems[i].label);
        uint16_t itemId;
        uint32_t addr = sym->st_value + gKeyItems[i].offset;
        fseek(elfFile, addr - sh_scripts->sh_addr + sh_scripts->sh_offset, SEEK_SET);
        if (!fread(&itemId, 2, 1, elfFile))
            FATAL_ERROR("fread");
        if (itemId != gKeyItems[i].vanillaItem)
            FATAL_ERROR("Expected item %d = 0x%X, got 0x%X\n", i, gKeyItems[i].vanillaItem, itemId);
        print("PlotlessKeyItems[]=0x%X\n", addr & 0xFFFFFF);
    }

    config_sym("PokedexOrder", "sSpeciesToNationalPokedexNum");
    config_sym("CheckValueOffset", "gRandomizerCheckValue");

    DestroyResources();
    fclose(outFile);
    fclose(elfFile);
    return 0;
}
