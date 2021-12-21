#include "global.h"
#include "gflib.h"
#include "random.h"
#include "overworld.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/moves.h"
#include "load_save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail_data.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "speedchoice.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mevent.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"
#include "done_button.h"

// this file's functions
static void ResetMiniGamesResults(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < 4; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_INST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SET;
    gSaveBlock2Ptr->optionsBattleScene = OPTIONS_BATTLE_SCENE_OFF;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_L_EQUALS_A;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

static void ClearBattleTower(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
}

static void WarpToPlayersRoom(void)
{
    switch (gSaveBlock2Ptr->speedchoiceConfig.startLocation) {
        case START_LOCATION_NORMAL:
            SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
            break;
        case START_LOCATION_EEVEE:
            SetWarpDestination(MAP_GROUP(CELADON_CITY_CONDOMINIUMS_ROOF_ROOM), MAP_NUM(CELADON_CITY_CONDOMINIUMS_ROOF_ROOM), -1, 7, 4);
            break;
        case START_LOCATION_LAPRAS:
            SetWarpDestination(MAP_GROUP(SILPH_CO_7F), MAP_NUM(SILPH_CO_7F), -1, 1, 7);
            break;
        case START_LOCATION_SAFARI:
            SetWarpDestination(MAP_GROUP(FUCHSIA_CITY), MAP_NUM(FUCHSIA_CITY), -1, 24, 6);
            break;
        case START_LOCATION_TOWER:
            SetWarpDestination(MAP_GROUP(POKEMON_TOWER_7F), MAP_NUM(POKEMON_TOWER_7F), -1, 11, 5);
            break;
    }
    WarpIntoMap();
    sInIntro = FALSE;
    sInSubMenu = FALSE;
    sInBattle = FALSE;
    sInField = TRUE;
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagCursorPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop();
    ResetQuestLog();
    SeedWildEncounterRng(Random());
    ResetSpecialVars();
}

void NewGameInitData(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ClearBattleTower();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->field_AC = 1;
    gSaveBlock2Ptr->field_AD = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ResetFameChecker();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    ResetGameStats();
    ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    RS_EnableNationalPokedex();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearEnigmaBerries();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    UnionRoomChat_InitializeRegisteredTexts();
    ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags();
    WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();

    if (gSaveBlock2Ptr->speedchoiceConfig.earlyBike == EARLY_BIKE_YES)
        AddBagItem(ITEM_BICYCLE, 1);
    if (gSaveBlock2Ptr->speedchoiceConfig.raceGoal == GOAL_MANUAL)
        AddBagItem(ITEM_DONE_BUTTON, 1);
    FlagSet(FLAG_SYS_B_DASH);

    if (gSaveBlock2Ptr->speedchoiceConfig.startLocation != START_LOCATION_NORMAL) {
        // Give the player a weak Magikarp to prevent game crashes.
        struct Pokemon * mon = AllocZeroed(sizeof(struct Pokemon));
        if (mon != NULL)
        {
            u32 pid;
            u32 otid = T2_READ_32(gSaveBlock2Ptr->playerTrainerId);
            do {
                pid = Random32();
            } while (!IsShinyOtIdPersonality(otid, pid));
            CreateMon(mon, SPECIES_MAGIKARP, 1, 0, TRUE, pid, OT_ID_PLAYER_ID, 0);
            GiveMonToPlayer(mon);
            Free(mon);
        }
        // Show the POKEMON option in the start menu.
        FlagSet(FLAG_SYS_POKEMON_GET);
    }

#if DEVMODE
    {
        struct Pokemon * mon = AllocZeroed(sizeof(struct Pokemon));
        if (mon != NULL)
        {
            u32 pid;
            u32 otid = T2_READ_32(gSaveBlock2Ptr->playerTrainerId);
            do {
                pid = Random32();
            } while (!IsShinyOtIdPersonality(otid, pid));
            CreateMon(mon, SPECIES_MEWTWO, 100, 31, TRUE, pid, OT_ID_PLAYER_ID, 0);
            SetMonMoveSlot(mon, MOVE_PSYCHIC, 0);
            SetMonMoveSlot(mon, MOVE_THUNDERBOLT, 1);
            SetMonMoveSlot(mon, MOVE_ICE_BEAM, 2);
            SetMonMoveSlot(mon, MOVE_FLAMETHROWER, 3);
            GiveMonToPlayer(mon);
            Free(mon);
        }
    }
#endif //DEVMODE
}

static void ResetMiniGamesResults(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokeJumpResults();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}
