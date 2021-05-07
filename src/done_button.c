#include "global.h"
#include "main.h"
#include "task.h"
#include "bg.h"
#include "window.h"
#include "palette.h"
#include "malloc.h"
#include "sound.h"
#include "constants/songs.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "text.h"
#include "menu.h"
#include "done_button.h"
#include "overworld.h"
#include "text_window.h"
#include "text_window_graphics.h"
#include "string_util.h"
#include "event_data.h"

struct DoneButton
{
    MainCallback doneCallback;
    u8 taskId;
    u8 page;
    u16 tilemapBuffer[0x800];
};

extern u16 sOptionMenuPalette[1];
extern u16 sMainMenuTextPal[16];

EWRAM_DATA bool8 sInSubMenu = FALSE;
EWRAM_DATA bool8 sInBattle = FALSE;
EWRAM_DATA bool8 sInField = FALSE;
EWRAM_DATA bool8 sInIntro = FALSE;

// In order to track the intro timers, which occur before the Save Block gets initialized,
// we have a persistent timer state that starts from boot since Save Block is not initialized
// until slightly later. We add the timers to the save data when the game loads.
EWRAM_DATA struct FrameTimers gFrameTimers = {0};


static EWRAM_DATA struct DoneButton *doneButton = NULL;

static void DoneButtonCB(void);
static void PrintGameStatsPage(void);
static void Task_DoneButton(u8 taskId);
static void Task_DestroyDoneButton(u8 taskId);

void OpenDoneButton(MainCallback doneCallback);
void DrawDoneButtonFrame(void);

struct DoneButtonLineItem
{
    const u8 * name;
    const u8 * (*printfn)(enum DoneButtonStat stat, enum DoneButtonStat stat2); // string formatter for each type.
    enum DoneButtonStat stat;
    enum DoneButtonStat stat2;
};

#define TRY_INC_GAME_STAT(saveBlock, statName, max)                   \
do {                                                                  \
    if(gSaveBlock##saveBlock##Ptr->doneButtonStats.statName < max)    \
        gSaveBlock##saveBlock##Ptr->doneButtonStats.statName++;       \
}while(0)

// max is unused, copy paste from other macro
#define GET_GAME_STAT(saveBlock, statName, max)                  \
do {                                                             \
    return gSaveBlock##saveBlock##Ptr->doneButtonStats.statName; \
}while(0)

#define TRY_INC_GAME_STAT_BY(saveBlock, statName, add, max)                \
do {                                                                       \
    u32 diff = max - gSaveBlock##saveBlock##Ptr->doneButtonStats.statName; \
    if(diff > add)                                                         \
        gSaveBlock##saveBlock##Ptr->doneButtonStats.statName += add;       \
    else                                                                   \
        gSaveBlock##saveBlock##Ptr->doneButtonStats.statName = max;        \
}while(0)

// Hmm, 3 giant switches. Repetitive?
// TODO: Better way of handling?
void TryAddButtonStatBy(enum DoneButtonStat stat, u32 add)
{
    switch(stat)
    {
        // DoneButtonStats1
    case DB_FRAME_COUNT_TOTAL:
        TRY_INC_GAME_STAT_BY(2, frameCount, add, UINT_MAX);
        break;
    case DB_FRAME_COUNT_OW:
        TRY_INC_GAME_STAT_BY(2, owFrameCount, add, UINT_MAX);
        break;
    case DB_FRAME_COUNT_BATTLE:
        TRY_INC_GAME_STAT_BY(2, battleFrameCount, add, UINT_MAX);
        break;
    case DB_FRAME_COUNT_MENU:
        TRY_INC_GAME_STAT_BY(2, menuFrameCount, add, UINT_MAX);
        break;
    case DB_FRAME_COUNT_INTROS:
        TRY_INC_GAME_STAT_BY(2, introsFrameCount, add, UINT_MAX);
        break;
    case DB_SAVE_COUNT:
        TRY_INC_GAME_STAT_BY(2, saveCount, add, USHRT_MAX);
        break;
    case DB_RELOAD_COUNT:
        TRY_INC_GAME_STAT_BY(2, reloadCount, add, USHRT_MAX);
        break;
    case DB_STEP_COUNT:
        TRY_INC_GAME_STAT_BY(2, stepCount, add, UINT_MAX);
        break;
    case DB_STEP_COUNT_WALK:
        TRY_INC_GAME_STAT_BY(2, stepCountWalk, add, UINT_MAX);
        break;
    case DB_STEP_COUNT_SURF:
        TRY_INC_GAME_STAT_BY(2, stepCountSurf, add, UINT_MAX);
        break;
    case DB_STEP_COUNT_BIKE:
        TRY_INC_GAME_STAT_BY(2, stepCountBike, add, UINT_MAX);
        break;
    case DB_STEP_COUNT_RUN:
        TRY_INC_GAME_STAT_BY(2, stepCountRun, add, UINT_MAX);
        break;
    case DB_BONKS:
        TRY_INC_GAME_STAT_BY(2, bonks, add, USHRT_MAX);
        break;
    case DB_TOTAL_DAMAGE_DEALT:
        TRY_INC_GAME_STAT_BY(2, totalDamageDealt, add, UINT_MAX);
        break;
    case DB_ACTUAL_DAMAGE_DEALT:
        TRY_INC_GAME_STAT_BY(2, actualDamageDealt, add, UINT_MAX);
        break;
    case DB_TOTAL_DAMAGE_TAKEN:
        TRY_INC_GAME_STAT_BY(2, totalDamageTaken, add, UINT_MAX);
        break;
    case DB_ACTUAL_DAMAGE_TAKEN:
        TRY_INC_GAME_STAT_BY(2, actualDamageTaken, add, UINT_MAX);
        break;
    case DB_OWN_MOVES_HIT:
        TRY_INC_GAME_STAT_BY(2, ownMovesHit, add, USHRT_MAX);
        break;
    case DB_OWN_MOVES_MISSED:
        TRY_INC_GAME_STAT_BY(2, ownMovesMissed, add, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_HIT:
        TRY_INC_GAME_STAT_BY(2, enemyMovesHit, add, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_MISSED:
        TRY_INC_GAME_STAT_BY(2, enemyMovesMissed, add, USHRT_MAX);
        break;
        // DoneButtonStats2
    case DB_OWN_MOVES_SE:
        TRY_INC_GAME_STAT_BY(2, ownMovesSE, add, USHRT_MAX);
        break;
    case DB_OWN_MOVES_NVE:
        TRY_INC_GAME_STAT_BY(2, ownMovesNVE, add, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_SE:
        TRY_INC_GAME_STAT_BY(2, enemyMovesSE, add, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_NVE:
        TRY_INC_GAME_STAT_BY(2, enemyMovesNVE, add, USHRT_MAX);
        break;
    case DB_CRITS_DEALT:
        TRY_INC_GAME_STAT_BY(2, critsDealt, add, USHRT_MAX);
        break;
    case DB_OHKOS_DEALT:
        TRY_INC_GAME_STAT_BY(2, OHKOsDealt, add, USHRT_MAX);
        break;
    case DB_CRITS_TAKEN:
        TRY_INC_GAME_STAT_BY(2, critsTaken, add, USHRT_MAX);
        break;
    case DB_OHKOS_TAKEN:
        TRY_INC_GAME_STAT_BY(2, OHKOsTaken, add, USHRT_MAX);
        break;
    case DB_PLAYER_HP_HEALED:
        TRY_INC_GAME_STAT_BY(2, playerHPHealed, add, UINT_MAX);
        break;
    case DB_ENEMY_HP_HEALED:
        TRY_INC_GAME_STAT_BY(2, enemyHPHealed, add, UINT_MAX);
        break;
    case DB_PLAYER_POKEMON_FAINTED:
        TRY_INC_GAME_STAT_BY(2, playerPokemonFainted, add, USHRT_MAX);
        break;
    case DB_ENEMY_POKEMON_FAINTED:
        TRY_INC_GAME_STAT_BY(2, enemyPokemonFainted, add, USHRT_MAX);
        break;
    case DB_EXP_GAINED:
        TRY_INC_GAME_STAT_BY(2, expGained, add, UINT_MAX);
        break;
    case DB_SWITCHOUTS:
        TRY_INC_GAME_STAT_BY(2, switchouts, add, USHRT_MAX);
        break;
    case DB_BATTLES:
        TRY_INC_GAME_STAT_BY(2, battles, add, USHRT_MAX);
        break;
    case DB_TRAINER_BATTLES:
        TRY_INC_GAME_STAT_BY(2, trainerBattles, add, USHRT_MAX);
        break;
    case DB_WILD_BATTLES:
        TRY_INC_GAME_STAT_BY(2, wildBattles, add, USHRT_MAX);
        break;
    case DB_BATTLES_FLED:
        TRY_INC_GAME_STAT_BY(2, battlesFled, add, USHRT_MAX);
        break;
    case DB_FAILED_RUNS:
        TRY_INC_GAME_STAT_BY(2, failedRuns, add, USHRT_MAX);
        break;
    case DB_MONEY_MADE:
        TRY_INC_GAME_STAT_BY(2, moneyMade, add, UINT_MAX);
        break;
    case DB_MONEY_SPENT:
        TRY_INC_GAME_STAT_BY(2, moneySpent, add, UINT_MAX);
        break;
    case DB_MONEY_LOST:
        TRY_INC_GAME_STAT_BY(2, moneyLost, add, UINT_MAX);
        break;
    case DB_ITEMS_PICKED_UP:
        TRY_INC_GAME_STAT_BY(2, itemsPickedUp, add, USHRT_MAX);
        break;
    case DB_ITEMS_BOUGHT:
        TRY_INC_GAME_STAT_BY(2, itemsBought, add, USHRT_MAX);
        break;
    case DB_ITEMS_SOLD:
        TRY_INC_GAME_STAT_BY(2, itemsSold, add, USHRT_MAX);
        break;
    case DB_MOVES_LEARNT:
        TRY_INC_GAME_STAT_BY(2, movesLearnt, add, USHRT_MAX);
        break;
    case DB_BALLS_THROWN:
        TRY_INC_GAME_STAT_BY(2, ballsThrown, add, USHRT_MAX);
        break;
    case DB_POKEMON_CAUGHT_IN_BALLS:
        TRY_INC_GAME_STAT_BY(2, pokemonCaughtInBalls, add, USHRT_MAX);
        break;
    case DB_EVOLUTIONS_ATTEMPTED:
        TRY_INC_GAME_STAT_BY(2, evosAttempted, add, UINT_MAX);
        break;
    case DB_EVOLUTIONS_COMPLETED:
        TRY_INC_GAME_STAT_BY(2, evosCompleted, add, UINT_MAX);
        break;
    case DB_EVOLUTIONS_CANCELLED:
        TRY_INC_GAME_STAT_BY(2, evosCancelled, add, UINT_MAX);
        break;
    }
}

void TryIncrementButtonStat(enum DoneButtonStat stat)
{
    switch(stat)
    {
        // DoneButtonStats1
    case DB_FRAME_COUNT_TOTAL:
        TRY_INC_GAME_STAT(2, frameCount, UINT_MAX);
        break;
    case DB_FRAME_COUNT_OW:
        TRY_INC_GAME_STAT(2, owFrameCount, UINT_MAX);
        break;
    case DB_FRAME_COUNT_BATTLE:
        TRY_INC_GAME_STAT(2, battleFrameCount, UINT_MAX);
        break;
    case DB_FRAME_COUNT_MENU:
        TRY_INC_GAME_STAT(2, menuFrameCount, UINT_MAX);
        break;
    case DB_FRAME_COUNT_INTROS: // This needs special handling due to intro not having loaded save block yet.
        TRY_INC_GAME_STAT(2, introsFrameCount, UINT_MAX);
        break;
    case DB_SAVE_COUNT:
        TRY_INC_GAME_STAT(2, saveCount, USHRT_MAX);
        break;
    case DB_RELOAD_COUNT:
        TRY_INC_GAME_STAT(2, reloadCount, USHRT_MAX);
        break;
    case DB_STEP_COUNT:
        TRY_INC_GAME_STAT(2, stepCount, UINT_MAX);
        break;
    case DB_STEP_COUNT_WALK:
        TRY_INC_GAME_STAT(2, stepCountWalk, UINT_MAX);
        break;
    case DB_STEP_COUNT_SURF:
        TRY_INC_GAME_STAT(2, stepCountSurf, UINT_MAX);
        break;
    case DB_STEP_COUNT_BIKE:
        TRY_INC_GAME_STAT(2, stepCountBike, UINT_MAX);
        break;
    case DB_STEP_COUNT_RUN:
        TRY_INC_GAME_STAT(2, stepCountRun, UINT_MAX);
        break;
    case DB_BONKS:
        TRY_INC_GAME_STAT(2, bonks, USHRT_MAX);
        break;
    case DB_TOTAL_DAMAGE_DEALT:
        TRY_INC_GAME_STAT(2, totalDamageDealt, UINT_MAX);
        break;
    case DB_ACTUAL_DAMAGE_DEALT:
        TRY_INC_GAME_STAT(2, actualDamageDealt, UINT_MAX);
        break;
    case DB_TOTAL_DAMAGE_TAKEN:
        TRY_INC_GAME_STAT(2, totalDamageTaken, UINT_MAX);
        break;
    case DB_ACTUAL_DAMAGE_TAKEN:
        TRY_INC_GAME_STAT(2, actualDamageTaken, UINT_MAX);
        break;
    case DB_OWN_MOVES_HIT:
        TRY_INC_GAME_STAT(2, ownMovesHit, USHRT_MAX);
        break;
    case DB_OWN_MOVES_MISSED:
        TRY_INC_GAME_STAT(2, ownMovesMissed, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_HIT:
        TRY_INC_GAME_STAT(2, enemyMovesHit, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_MISSED:
        TRY_INC_GAME_STAT(2, enemyMovesMissed, USHRT_MAX);
        break;
        // DoneButtonStats2
    case DB_OWN_MOVES_SE:
        TRY_INC_GAME_STAT(2, ownMovesSE, USHRT_MAX);
        break;
    case DB_OWN_MOVES_NVE:
        TRY_INC_GAME_STAT(2, ownMovesNVE, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_SE:
        TRY_INC_GAME_STAT(2, enemyMovesSE, USHRT_MAX);
        break;
    case DB_ENEMY_MOVES_NVE:
        TRY_INC_GAME_STAT(2, enemyMovesNVE, USHRT_MAX);
        break;
    case DB_CRITS_DEALT:
        TRY_INC_GAME_STAT(2, critsDealt, USHRT_MAX);
        break;
    case DB_OHKOS_DEALT:
        TRY_INC_GAME_STAT(2, OHKOsDealt, USHRT_MAX);
        break;
    case DB_CRITS_TAKEN:
        TRY_INC_GAME_STAT(2, critsTaken, USHRT_MAX);
        break;
    case DB_OHKOS_TAKEN:
        TRY_INC_GAME_STAT(2, OHKOsTaken, USHRT_MAX);
        break;
    case DB_PLAYER_HP_HEALED:
        TRY_INC_GAME_STAT(2, playerHPHealed, UINT_MAX);
        break;
    case DB_ENEMY_HP_HEALED:
        TRY_INC_GAME_STAT(2, enemyHPHealed, UINT_MAX);
        break;
    case DB_PLAYER_POKEMON_FAINTED:
        TRY_INC_GAME_STAT(2, playerPokemonFainted, USHRT_MAX);
        break;
    case DB_ENEMY_POKEMON_FAINTED:
        TRY_INC_GAME_STAT(2, enemyPokemonFainted, USHRT_MAX);
        break;
    case DB_EXP_GAINED:
        TRY_INC_GAME_STAT(2, expGained, UINT_MAX);
        break;
    case DB_SWITCHOUTS:
        TRY_INC_GAME_STAT(2, switchouts, USHRT_MAX);
        break;
    case DB_BATTLES:
        TRY_INC_GAME_STAT(2, battles, USHRT_MAX);
        break;
    case DB_TRAINER_BATTLES:
        TRY_INC_GAME_STAT(2, trainerBattles, USHRT_MAX);
        break;
    case DB_WILD_BATTLES:
        TRY_INC_GAME_STAT(2, wildBattles, USHRT_MAX);
        break;
    case DB_BATTLES_FLED:
        TRY_INC_GAME_STAT(2, battlesFled, USHRT_MAX);
        break;
    case DB_FAILED_RUNS:
        TRY_INC_GAME_STAT(2, failedRuns, USHRT_MAX);
        break;
    case DB_MONEY_MADE:
        TRY_INC_GAME_STAT(2, moneyMade, UINT_MAX);
        break;
    case DB_MONEY_SPENT:
        TRY_INC_GAME_STAT(2, moneySpent, UINT_MAX);
        break;
    case DB_MONEY_LOST:
        TRY_INC_GAME_STAT(2, moneyLost, UINT_MAX);
        break;
    case DB_ITEMS_PICKED_UP:
        TRY_INC_GAME_STAT(2, itemsPickedUp, USHRT_MAX);
        break;
    case DB_ITEMS_BOUGHT:
        TRY_INC_GAME_STAT(2, itemsBought, USHRT_MAX);
        break;
    case DB_ITEMS_SOLD:
        TRY_INC_GAME_STAT(2, itemsSold, USHRT_MAX);
        break;
    case DB_MOVES_LEARNT:
        TRY_INC_GAME_STAT(2, movesLearnt, USHRT_MAX);
        break;
    case DB_BALLS_THROWN:
        TRY_INC_GAME_STAT(2, ballsThrown, USHRT_MAX);
        break;
    case DB_POKEMON_CAUGHT_IN_BALLS:
        TRY_INC_GAME_STAT(2, pokemonCaughtInBalls, USHRT_MAX);
        break;
    case DB_EVOLUTIONS_ATTEMPTED:
        TRY_INC_GAME_STAT(2, evosAttempted, UINT_MAX);
        break;
    case DB_EVOLUTIONS_COMPLETED:
        TRY_INC_GAME_STAT(2, evosCompleted, UINT_MAX);
        break;
    case DB_EVOLUTIONS_CANCELLED:
        TRY_INC_GAME_STAT(2, evosCancelled, UINT_MAX);
        break;
    }
}

u32 GetDoneButtonStat(enum DoneButtonStat stat)
{
    switch(stat)
    {
        // DoneButtonStats1
    case DB_FRAME_COUNT_TOTAL:
        GET_GAME_STAT(2, frameCount, UINT_MAX);
    case DB_FRAME_COUNT_OW:
        GET_GAME_STAT(2, owFrameCount, UINT_MAX);
    case DB_FRAME_COUNT_BATTLE:
        GET_GAME_STAT(2, battleFrameCount, UINT_MAX);
    case DB_FRAME_COUNT_MENU:
        GET_GAME_STAT(2, menuFrameCount, UINT_MAX);
    case DB_FRAME_COUNT_INTROS: // This needs special handling due to intro not having loaded save block yet.
        GET_GAME_STAT(2, introsFrameCount, UINT_MAX);
    case DB_SAVE_COUNT:
        GET_GAME_STAT(2, saveCount, USHRT_MAX);
    case DB_RELOAD_COUNT:
        GET_GAME_STAT(2, reloadCount, USHRT_MAX);
    case DB_STEP_COUNT:
        GET_GAME_STAT(2, stepCount, UINT_MAX);
    case DB_STEP_COUNT_WALK:
        GET_GAME_STAT(2, stepCountWalk, UINT_MAX);
    case DB_STEP_COUNT_SURF:
        GET_GAME_STAT(2, stepCountSurf, UINT_MAX);
    case DB_STEP_COUNT_BIKE:
        GET_GAME_STAT(2, stepCountBike, UINT_MAX);
    case DB_STEP_COUNT_RUN:
        GET_GAME_STAT(2, stepCountRun, UINT_MAX);
    case DB_BONKS:
        GET_GAME_STAT(2, bonks, USHRT_MAX);
    case DB_TOTAL_DAMAGE_DEALT:
        GET_GAME_STAT(2, totalDamageDealt, UINT_MAX);
    case DB_ACTUAL_DAMAGE_DEALT:
        GET_GAME_STAT(2, actualDamageDealt, UINT_MAX);
    case DB_TOTAL_DAMAGE_TAKEN:
        GET_GAME_STAT(2, totalDamageTaken, UINT_MAX);
    case DB_ACTUAL_DAMAGE_TAKEN:
        GET_GAME_STAT(2, actualDamageTaken, UINT_MAX);
    case DB_OWN_MOVES_HIT:
        GET_GAME_STAT(2, ownMovesHit, USHRT_MAX);
    case DB_OWN_MOVES_MISSED:
        GET_GAME_STAT(2, ownMovesMissed, USHRT_MAX);
    case DB_ENEMY_MOVES_HIT:
        GET_GAME_STAT(2, enemyMovesHit, USHRT_MAX);
    case DB_ENEMY_MOVES_MISSED:
        GET_GAME_STAT(2, enemyMovesMissed, USHRT_MAX);
        // DoneButtonStats2
    case DB_OWN_MOVES_SE:
        GET_GAME_STAT(2, ownMovesSE, USHRT_MAX);
    case DB_OWN_MOVES_NVE:
        GET_GAME_STAT(2, ownMovesNVE, USHRT_MAX);
    case DB_ENEMY_MOVES_SE:
        GET_GAME_STAT(2, enemyMovesSE, USHRT_MAX);
    case DB_ENEMY_MOVES_NVE:
        GET_GAME_STAT(2, enemyMovesNVE, USHRT_MAX);
    case DB_CRITS_DEALT:
        GET_GAME_STAT(2, critsDealt, USHRT_MAX);
    case DB_OHKOS_DEALT:
        GET_GAME_STAT(2, OHKOsDealt, USHRT_MAX);
    case DB_CRITS_TAKEN:
        GET_GAME_STAT(2, critsTaken, USHRT_MAX);
    case DB_OHKOS_TAKEN:
        GET_GAME_STAT(2, OHKOsTaken, USHRT_MAX);
    case DB_PLAYER_HP_HEALED:
        GET_GAME_STAT(2, playerHPHealed, UINT_MAX);
    case DB_ENEMY_HP_HEALED:
        GET_GAME_STAT(2, enemyHPHealed, UINT_MAX);
    case DB_PLAYER_POKEMON_FAINTED:
        GET_GAME_STAT(2, playerPokemonFainted, USHRT_MAX);
    case DB_ENEMY_POKEMON_FAINTED:
        GET_GAME_STAT(2, enemyPokemonFainted, USHRT_MAX);
    case DB_EXP_GAINED:
        GET_GAME_STAT(2, expGained, UINT_MAX);
    case DB_SWITCHOUTS:
        GET_GAME_STAT(2, switchouts, USHRT_MAX);
    case DB_BATTLES:
        GET_GAME_STAT(2, battles, USHRT_MAX);
    case DB_TRAINER_BATTLES:
        GET_GAME_STAT(2, trainerBattles, USHRT_MAX);
    case DB_WILD_BATTLES:
        GET_GAME_STAT(2, wildBattles, USHRT_MAX);
    case DB_BATTLES_FLED:
        GET_GAME_STAT(2, battlesFled, USHRT_MAX);
    case DB_FAILED_RUNS:
        GET_GAME_STAT(2, failedRuns, USHRT_MAX);
    case DB_MONEY_MADE:
        GET_GAME_STAT(2, moneyMade, UINT_MAX);
    case DB_MONEY_SPENT:
        GET_GAME_STAT(2, moneySpent, UINT_MAX);
    case DB_MONEY_LOST:
        GET_GAME_STAT(2, moneyLost, UINT_MAX);
    case DB_ITEMS_PICKED_UP:
        GET_GAME_STAT(2, itemsPickedUp, USHRT_MAX);
    case DB_ITEMS_BOUGHT:
        GET_GAME_STAT(2, itemsBought, USHRT_MAX);
    case DB_ITEMS_SOLD:
        GET_GAME_STAT(2, itemsSold, USHRT_MAX);
    case DB_MOVES_LEARNT:
        GET_GAME_STAT(2, movesLearnt, USHRT_MAX);
    case DB_BALLS_THROWN:
        GET_GAME_STAT(2, ballsThrown, USHRT_MAX);
    case DB_POKEMON_CAUGHT_IN_BALLS:
        GET_GAME_STAT(2, pokemonCaughtInBalls, USHRT_MAX);
    case DB_EVOLUTIONS_ATTEMPTED:
        GET_GAME_STAT(2, evosAttempted, UINT_MAX);
    case DB_EVOLUTIONS_COMPLETED:
        GET_GAME_STAT(2, evosCompleted, UINT_MAX);
    case DB_EVOLUTIONS_CANCELLED:
        GET_GAME_STAT(2, evosCancelled, UINT_MAX);
    }
}

const u8 *GetStringSample(void)
{
    return NULL; // TODO
}

struct LocalFrameTimerLoad
{
    u32 totalFrames;
    u32 totalFramesOw;
    u32 totalFramesBattle;
    u32 totalFramesMenu;
    u32 totalFramesIntro;
};

EWRAM_DATA struct LocalFrameTimerLoad gLocalFrameTimers = {0};

const u8 gTODOString[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TODO");

// PAGE 1
const u8 gTimersHeader[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (TIMERS)");
const u8 gTimersTotalTime[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TOTAL TIME: ");
const u8 gTimersOverworldTime[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}OVERWORLD TIME: ");
const u8 gTimersTimeInBattle[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TIME IN BATTLE: ");
const u8 gTimersTimeInMenus[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TIME IN MENUS: ");
const u8 gTimersTimeInIntros[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TIME IN INTROS: ");

// PAGE 2
const u8 gMovementHeader[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (MOVEMENT)");
const u8 gMovementTotalSteps[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TOTAL STEPS: ");
const u8 gMovementStepsWalked[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}STEPS WALKED: ");
const u8 gMovementStepsBiked[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}STEPS BIKED: ");
const u8 gMovementStepsSurfed[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}STEPS SURFED: ");
const u8 gMovementStepsRan[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}STEPS RAN: ");
const u8 gMovementBonks[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}BONKS: ");

// PAGE 3
const u8 gBattle1Header[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (BATTLE 1)");
const u8 gBattle1TotalBattles[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TOTAL BATTLES: ");
const u8 gBattle1WildBattles[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}WILD BATTLES: ");
const u8 gBattle1TrainerBattles[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TRAINER BATTLES: ");
const u8 gBattle1BattlesFledFrom[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}BATTLES FLED FROM: ");
const u8 gBattle1FailedEscapes[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}FAILED ESCAPES: ");

// PAGE 4
const u8 gBattle2Header[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (BATTLE 2)");
const u8 gBattle2EnemyPkmnFainted[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}ENEMY PKMN FAINTED: ");
const u8 gBattle2ExpGained[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}EXP GAINED: ");
const u8 gBattle2OwnPkmnFainted[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}OWN PKMN FAINTED: ");
const u8 gBattle2NumSwitchouts[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}NUM SWITCHOUTS: ");
const u8 gBattle2BallsThrown[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}BALLS THROWN: ");
const u8 gBattle2PkmnCaptured[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PKMN CAPTURED: ");

// PAGE 5
const u8 gBattle3Header[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (BATTLE 3)");
const u8 gBattle3MovesHitBy[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}MOVES HIT BY: ");
const u8 gBattle3MovesMissed[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}MOVES MISSED: ");
const u8 gBattle3SEMovesUsed[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}S.E. MOVES USED: ");
const u8 gBattle3NVEMovesUsed[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}N.V.E. MOVES USED: ");
const u8 gBattle3CriticalHits[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}CRITICAL HITS: ");
const u8 gBattle3OHKOs[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}OHKOs: ");

// PAGE 6
const u8 gBattle4Header[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (BATTLE 4)");
const u8 gBattle4DamageDealt[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}DAMAGE DEALT: ");
const u8 gBattle4DamageTaken[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}DAMAGE TAKEN: ");

// PAGE 7
const u8 gMoneyItemsHeader[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (MONEY & ITEMS)");
const u8 gMoneyItemsMoneyMade[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}MONEY MADE: ");
const u8 gMoneyItemsMoneySpent[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}MONEY SPENT: ");
const u8 gMoneyItemsMoneyLost[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}MONEY LOST: ");
const u8 gMoneyItemsItemsPickedUp[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}ITEMS PICKED UP: ");
const u8 gMoneyItemsItemsBought[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}ITEMS BOUGHT: ");
const u8 gMoneyItemsItemsSold[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}ITEMS SOLD: ");

// PAGE 8
const u8 gMiscHeader[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}PLAYER STATS (MISC.)");
const u8 gMiscTimesSaved[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}TIMES SAVED: ");
const u8 gMiscSaveReloads[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}SAVE RELOADS: ");
const u8 gMiscEvosAttempted[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}EVOS ATTEMPTED: ");
const u8 gMiscEvosCompleted[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}EVOS COMPLETED: ");
const u8 gMiscEvosCancelled[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}EVOS CANCELLED: ");

const u8 gPageText[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}{LEFT_ARROW} PAGE {STR_VAR_1} {RIGHT_ARROW}");

#define CHAR_0 0xA1

EWRAM_DATA u8 gBufferedString[18] = {0}; // Timer
EWRAM_DATA u8 gBufferedString2[13] = {0}; // Standard 6 digit stats
EWRAM_DATA u8 gBufferedString3[15] = {0}; // Standard 6 digit stats + (secondary stat)

const u8 *GetFormattedFrameTimerStr(enum DoneButtonStat stat, enum DoneButtonStat stat2)
{
    u32 frames; // guaranteed to be one of the timer ones.
    u32 hours;
    u32 minutes;
    u32 seconds;
    u32 milliseconds;

    switch(stat)
    {
    case DB_FRAME_COUNT_TOTAL:
        frames = gLocalFrameTimers.totalFrames;
        break;
    case DB_FRAME_COUNT_OW:
        frames = gLocalFrameTimers.totalFramesOw;
        break;
    case DB_FRAME_COUNT_BATTLE:
        frames = gLocalFrameTimers.totalFramesBattle;
        break;
    case DB_FRAME_COUNT_MENU:
        frames = gLocalFrameTimers.totalFramesMenu;
        break;
    case DB_FRAME_COUNT_INTROS:
        frames = gLocalFrameTimers.totalFramesIntro;
        break;
    }

    seconds = frames / 60;
    milliseconds = frames - (seconds * 60);
    minutes = seconds / 60;
    seconds = seconds - (minutes * 60);
    hours = minutes / 60;
    minutes = minutes - (hours * 60);

    gBufferedString[0] = EXT_CTRL_CODE_BEGIN;
    gBufferedString[1] = EXT_CTRL_CODE_COLOR;
    gBufferedString[2] = TEXT_COLOR_RED;
    gBufferedString[3] = EXT_CTRL_CODE_BEGIN;
    gBufferedString[4] = EXT_CTRL_CODE_SHADOW;
    gBufferedString[5] = TEXT_COLOR_LIGHT_RED;
    gBufferedString[6] = CHAR_0 + (hours / 10);
    gBufferedString[7] = CHAR_0 + (hours % 10);
    gBufferedString[8] = CHAR_COLON; // ':'
    gBufferedString[9] = CHAR_0 + (minutes / 10);
    gBufferedString[10] = CHAR_0 + (minutes % 10);
    gBufferedString[11] = CHAR_COLON; // ':'
    gBufferedString[12] = CHAR_0 + (seconds / 10);
    gBufferedString[13] = CHAR_0 + (seconds % 10);
    gBufferedString[14] = CHAR_PERIOD; // '.'
    gBufferedString[15] = CHAR_0 + (milliseconds / 10);
    gBufferedString[16] = CHAR_0 + (milliseconds % 10);
    gBufferedString[17] = 0xFF;

    return (const u8 *)gBufferedString;
}

const u8 gBufferedString4[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}{STR_VAR_1}");
const u8 gBufferedString5[] = _("{COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}{STR_VAR_1}({STR_VAR_2})");

int GetNumDigits(int n)
{
    int count = 0;
    while(n != 0)
    {
        n /= 10;
        ++count;
    }
    if(count == 0)
        count = 1;
    return count;
}

const u8 *GetStandardButtonStat(enum DoneButtonStat stat, enum DoneButtonStat stat2)
{
    u32 number = GetDoneButtonStat(stat);

    if(number > 999999)
        number = 999999;

    ConvertIntToDecimalStringN(gStringVar1, number, STR_CONV_MODE_RIGHT_ALIGN, GetNumDigits(number));
    StringExpandPlaceholders(gStringVar4, gBufferedString4);
    return gStringVar4;
}

const u8 *GetStandardDoubleButtonStat(enum DoneButtonStat stat, enum DoneButtonStat stat2)
{
    u32 number1 = GetDoneButtonStat(stat);
    u32 number2 = GetDoneButtonStat(stat2);

    if(number1 > 999999)
        number1 = 999999;

    if(number2 > 999999)
        number2 = 999999;

    ConvertIntToDecimalStringN(gStringVar1, number1, STR_CONV_MODE_RIGHT_ALIGN, GetNumDigits(number1));
    ConvertIntToDecimalStringN(gStringVar2, number2, STR_CONV_MODE_RIGHT_ALIGN, GetNumDigits(number2));
    StringExpandPlaceholders(gStringVar4, gBufferedString5);
    return gStringVar4;
}

const struct DoneButtonLineItem sLineItems[8][7] = {
    { // PAGE 1 (TODO)
        {gTimersHeader, NULL},
        {gTimersTotalTime, GetFormattedFrameTimerStr, DB_FRAME_COUNT_TOTAL},
        {gTimersOverworldTime, GetFormattedFrameTimerStr, DB_FRAME_COUNT_OW},
        {gTimersTimeInBattle, GetFormattedFrameTimerStr, DB_FRAME_COUNT_BATTLE},
        {gTimersTimeInMenus, GetFormattedFrameTimerStr, DB_FRAME_COUNT_MENU},
        {gTimersTimeInIntros, GetFormattedFrameTimerStr, DB_FRAME_COUNT_INTROS},
        {NULL, NULL}
    },
    { // PAGE 2 (TODO)
        {gMovementHeader, NULL},
        {gMovementTotalSteps, GetStandardButtonStat, DB_STEP_COUNT},
        {gMovementStepsWalked, GetStandardButtonStat, DB_STEP_COUNT_WALK},
        {gMovementStepsBiked, GetStandardButtonStat, DB_STEP_COUNT_BIKE},
        {gMovementStepsSurfed, GetStandardButtonStat, DB_STEP_COUNT_SURF},
        {gMovementStepsRan, GetStandardButtonStat, DB_STEP_COUNT_RUN},
        {gMovementBonks, GetStandardButtonStat, DB_BONKS}
    },
    { // PAGE 3 (TODO)
        {gBattle1Header, NULL},
        {gBattle1TotalBattles, GetStandardButtonStat, DB_BATTLES},
        {gBattle1WildBattles, GetStandardButtonStat, DB_WILD_BATTLES},
        {gBattle1TrainerBattles, GetStandardButtonStat, DB_TRAINER_BATTLES},
        {gBattle1BattlesFledFrom, GetStandardButtonStat, DB_BATTLES_FLED},
        {gBattle1FailedEscapes, GetStandardButtonStat, DB_FAILED_RUNS},
        {NULL, NULL}
    },
    { // PAGE 4 (TODO)
        {gBattle2Header, NULL},
        {gBattle2EnemyPkmnFainted, GetStandardButtonStat, DB_ENEMY_POKEMON_FAINTED},
        {gBattle2ExpGained, GetStandardButtonStat, DB_EXP_GAINED},
        {gBattle2OwnPkmnFainted, GetStandardButtonStat, DB_PLAYER_POKEMON_FAINTED},
        {gBattle2NumSwitchouts, GetStandardButtonStat, DB_SWITCHOUTS},
        {gBattle2BallsThrown, GetStandardButtonStat, DB_BALLS_THROWN},
        {gBattle2PkmnCaptured, GetStandardButtonStat, DB_POKEMON_CAUGHT_IN_BALLS}
    },
    { // PAGE 5 (TODO)
        {gBattle3Header, NULL},
        {gBattle3MovesHitBy, GetStandardDoubleButtonStat, DB_OWN_MOVES_HIT, DB_ENEMY_MOVES_HIT}, // Players (Opponents)
        {gBattle3MovesMissed, GetStandardDoubleButtonStat, DB_OWN_MOVES_MISSED, DB_ENEMY_MOVES_MISSED}, // Players (Opponents)
        {gBattle3SEMovesUsed, GetStandardDoubleButtonStat, DB_OWN_MOVES_SE, DB_ENEMY_MOVES_SE}, // Players (Opponents)
        {gBattle3NVEMovesUsed, GetStandardDoubleButtonStat, DB_OWN_MOVES_NVE, DB_ENEMY_MOVES_NVE}, // Players (Opponents)
        {gBattle3CriticalHits, GetStandardDoubleButtonStat, DB_CRITS_DEALT, DB_CRITS_TAKEN}, // Players (Opponents)
        {gBattle3OHKOs, GetStandardDoubleButtonStat, DB_OHKOS_DEALT, DB_OHKOS_TAKEN} // Players (Opponents)
    },
    { // PAGE 6 (TODO)
        {gBattle4Header, NULL},
        {gBattle4DamageDealt, GetStandardDoubleButtonStat, DB_TOTAL_DAMAGE_DEALT, DB_ACTUAL_DAMAGE_DEALT}, // Total (Actual)
        {gBattle4DamageTaken, GetStandardDoubleButtonStat, DB_TOTAL_DAMAGE_TAKEN, DB_ACTUAL_DAMAGE_TAKEN}, // Total (Actual)
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL},
        {NULL, NULL}
    },
    { // PAGE 7 (TODO)
        {gMoneyItemsHeader, NULL},
        {gMoneyItemsMoneyMade, GetStandardButtonStat, DB_MONEY_MADE},
        {gMoneyItemsMoneySpent, GetStandardButtonStat, DB_MONEY_SPENT},
        {gMoneyItemsMoneyLost, GetStandardButtonStat, DB_MONEY_LOST},
        {gMoneyItemsItemsPickedUp, GetStandardButtonStat, DB_ITEMS_PICKED_UP},
        {gMoneyItemsItemsBought, GetStandardButtonStat, DB_ITEMS_BOUGHT},
        {gMoneyItemsItemsSold, GetStandardButtonStat, DB_ITEMS_SOLD}
    },
    { // PAGE 8 (TODO)
        {gMiscHeader, NULL},
        {gMiscTimesSaved, GetStandardButtonStat, DB_SAVE_COUNT},
        {gMiscSaveReloads, GetStandardButtonStat, DB_RELOAD_COUNT},
        {gMiscEvosAttempted, GetStandardButtonStat, DB_EVOLUTIONS_ATTEMPTED},
        {gMiscEvosCompleted, GetStandardButtonStat, DB_EVOLUTIONS_COMPLETED},
        {gMiscEvosCancelled, GetStandardButtonStat, DB_EVOLUTIONS_CANCELLED}
    }
};

#define NPAGES (NELEMS(sLineItems))

static const struct BgTemplate sSpeedchoiceDoneButtonTemplates[3] =
    {
        {
            .bg = 1,
            .charBaseIndex = 1,
            .mapBaseIndex = 30,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 1,
            .baseTile = 0
        },
        {
            .bg = 0,
            .charBaseIndex = 1,
            .mapBaseIndex = 31,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 2,
            .baseTile = 0
        },
        // 0x000001ec
        {
            .bg = 2,
            .charBaseIndex = 1,
            .mapBaseIndex = 29,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 0,
            .baseTile = 0
        }
    };

/*
    {1, 2, 1, 0x1A, 2, 1, 2},
    {0, 2, 5, 0x1A, 14, 1, 0x36},
    {2, 2, 15, 0x1A, 4, 15, 427},
    {2, 23, 9, 4, 4, 15, 531}, // YES/NO
    DUMMY_WIN_TEMPLATE
*/

static const struct WindowTemplate sWinTemplates[3] =
    {
        {
            .bg = 1,
            .tilemapLeft = 1,
            .tilemapTop = 1,
            .width = 28,
            .height = 18,
            .paletteNum = 1,
            .baseBlock = 427,
        },
        //{0, 2, 5, 0x1A, 14, 1, 0x36},
        DUMMY_WIN_TEMPLATE,
    };

void Task_InitDoneButtonMenu(u8 taskId)
{
    OpenDoneButton(CB2_ReturnToField);
    DestroyTask(taskId);
}

void OpenDoneButton(MainCallback doneCallback)
{
    doneButton = AllocZeroed(sizeof(*doneButton));
    if (doneButton == NULL)
        SetMainCallback2(doneCallback);
    else
    {
        doneButton->doneCallback = doneCallback;
        doneButton->taskId = 0xFF;
        doneButton->page = 0;
        SetMainCallback2(DoneButtonCB);
    }
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

extern const struct BgTemplate sMainMenuBgTemplates[];
extern const struct WindowTemplate sSpeedchoiceMenuWinTemplates[];

void Task_DoneButtonFadeIn(u8 taskId);

void DoneButtonCB(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
    {
        u8 *addr;
        u32 size;

        addr = (u8 *)VRAM;
        size = 0x18000;
        while (1)
        {
            DmaFill16(3, 0, addr, 0x1000);
            addr += 0x1000;
            size -= 0x1000;
            if (size <= 0x1000)
            {
                DmaFill16(3, 0, addr, size);
                break;
            }
        }
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sSpeedchoiceDoneButtonTemplates, NELEMS(sSpeedchoiceDoneButtonTemplates));
        ChangeBgX(0, 0, 0);
        ChangeBgY(0, 0, 0);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        ChangeBgX(3, 0, 0);
        ChangeBgY(3, 0, 0);
        InitWindows(sWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 5);
        SetGpuReg(REG_OFFSET_WINOUT, 39);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gMain.state++;
        break;
    }
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetUserFrameGraphicsInfo(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuPalette, 0, sizeof(sOptionMenuPalette));
        LoadPalette(GetUserFrameGraphicsInfo(gSaveBlock2Ptr->optionsWindowFrameType)->palette, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(stdpal_get(2), 0x10, 0x20);
        LoadPalette(sMainMenuTextPal, 0xF0, sizeof(sMainMenuTextPal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(0);
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        //PutWindowTilemap(1);
        //DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        DrawDoneButtonFrame();
        gLocalFrameTimers.totalFrames = GetDoneButtonStat(DB_FRAME_COUNT_TOTAL) + gFrameTimers.frameCount;
        gLocalFrameTimers.totalFramesOw = GetDoneButtonStat(DB_FRAME_COUNT_OW) + gFrameTimers.owFrameCount;
        gLocalFrameTimers.totalFramesBattle = GetDoneButtonStat(DB_FRAME_COUNT_BATTLE) + gFrameTimers.battleFrameCount;
        gLocalFrameTimers.totalFramesMenu = GetDoneButtonStat(DB_FRAME_COUNT_MENU) + gFrameTimers.menuFrameCount;
        gLocalFrameTimers.totalFramesIntro = GetDoneButtonStat(DB_FRAME_COUNT_INTROS) + gFrameTimers.introsFrameCount;
        gMain.state++;
        break;
    case 10:
        //FillWindowPixelBuffer(0, PIXEL_FILL(0));
        PlayBGM(MUS_NET_CENTER);
        PrintGameStatsPage();
        doneButton->taskId = CreateTask(Task_DoneButtonFadeIn, 0);
        gMain.state++;
        break;
    case 11:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        break;
    }
}

void Task_DoneButtonFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_DoneButton;
}

static void Task_DoneButton(u8 taskId)
{
    struct DoneButton *data = doneButton;

    if (JOY_NEW(DPAD_RIGHT))
    {
        PlaySE(SE_SELECT);
        if (++data->page >= NPAGES)
            data->page = 0;
        PrintGameStatsPage();
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        PlaySE(SE_SELECT);
        if (data->page == 0)
            data->page = NPAGES - 1;
        else
            data->page--;
        PrintGameStatsPage();
    }
    else if (JOY_NEW(A_BUTTON | B_BUTTON | START_BUTTON))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_DestroyDoneButton;
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    }
}

static void Task_DestroyDoneButton(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        FreeAllWindowBuffers();
        SetMainCallback2(doneButton->doneCallback);
        Free(doneButton);
        DestroyTask(taskId);
    }
}

// it doesnt seem centered right. subtract 8 pixels to compensate for these functions
void PrintPageHeader(const struct DoneButtonLineItem *item)
{
    s32 width = GetStringWidth(0, item->name, 0);
    s32 centered_x = ((29 * 8) - (1 * 8) - width) / 2;

    AddTextPrinterParameterized(0, 2, item->name, centered_x - 8, 1, -1, NULL);
}

void PrintPageString(void)
{
    struct DoneButton *data = doneButton;
    s32 width, centered_x;

    ConvertIntToDecimalStringN(gStringVar1, data->page + 1, STR_CONV_MODE_RIGHT_ALIGN, 1);
    StringExpandPlaceholders(gStringVar4, gPageText);
    width = GetStringWidth(0, gStringVar4, 0);
    centered_x = (240 - width) / 2;

    AddTextPrinterParameterized(0, 2, gStringVar4, centered_x - 8, 128, -1, NULL);
}

static void PrintGameStatsPage(void)
{
    const struct DoneButtonLineItem * items = sLineItems[doneButton->page];
    s32 i;

    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    for (i = 0; i < 7; i++)
    {
        s32 width;
        const u8 * value_s;
        if(i == 0 && items[i].name) // this is the header. special treatment
            PrintPageHeader(&items[i]);
        else
        {
            if (items[i].name != NULL)
            {
                AddTextPrinterParameterized(0, 2, items[i].name, 1, 18 * i + 1, -1, NULL);
            }
            if (items[i].printfn != NULL)
            {
                value_s = items[i].printfn(items[i].stat, items[i].stat2);
            }
            else
            {
                value_s = gTODOString;
            }
            width = GetStringWidth(0, value_s, 0);
            if (items[i].name != NULL)
            {
                if(doneButton->page + 1 == 1) // timer spacing handling
                    AddTextPrinterParameterized(0, 2, value_s, 216 - width, 18 * i + 1, -1, NULL);
                else
                    AddTextPrinterParameterized(0, 2, value_s, 192 - width, 18 * i + 1, -1, NULL);
            }
        }
    }
    PrintPageString();
    PutWindowTilemap(0);
    CopyWindowToVram(0, 3);
}

void DrawDoneButtonFrame(void)
{
    //                   bg, tileNum, x,    y,    width, height,  pal
    FillBgTilemapBufferRect(1, 0x1A2, 0,    0,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A3, 1,    0,      0x1C,   1,      7);
    FillBgTilemapBufferRect(1, 0x1A4, 29,   0,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A5, 0,    1,      1,      0x16,   7);
    FillBgTilemapBufferRect(1, 0x1A7, 29,   1,      1,      0x16,   7);
    FillBgTilemapBufferRect(1, 0x1A8, 0,    19,     1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A9, 1,    19,     0x1C,   1,      7);
    FillBgTilemapBufferRect(1, 0x1AA, 29,   19,     1,      1,      7);

    CopyBgTilemapBufferToVram(1);
}
