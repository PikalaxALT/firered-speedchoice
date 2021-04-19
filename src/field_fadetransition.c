#include "global.h"
#include "gflib.h"
#include "field_fadetransition.h"
#include "overworld.h"
#include "fldeff.h"
#include "field_weather.h"
#include "map_preview_screen.h"
#include "field_player_avatar.h"
#include "task.h"
#include "script.h"
#include "cable_club.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "quest_log.h"
#include "link.h"
#include "event_object_movement.h"
#include "field_door.h"
#include "field_effect.h"
#include "field_screen_effect.h"
#include "field_specials.h"
#include "event_object_lock.h"
#include "start_menu.h"
#include "constants/songs.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/field_weather.h"

static void DoWarpDoorFadeIn(u8 fadeFromBlack);
static void Task_OpenHingedDoor(u8 taskId);
static void Task_ExitNonAnimDoor(u8 taskId);
static void Task_WarpIntoMapAnim_Generic(u8 taskId);
static void Task_TeleportWarpIn(u8 taskId);
static void Task_Teleport2Warp(u8 taskId);
static void Task_TeleportWarp(u8 taskId);
static void Task_DoorWarp(u8 taskId);
static void Task_StairWarp(u8 taskId);
static void InitStairWarpOut(u16, s16*, s16*);
static void GetStairSpeedVecByMetatileBehavior(u8 metatileBehavior, s16 *pXspeed, s16 *pYspeed);
static void UpdateStairWarpOut(s16, s16, s16*, s16*, s16*);
static void Task_WarpIntoMapAnim_DirectionalStairs(u8 taskId);
static void InitStairWarpIn(s16 *, s16 *, s16 *, s16 *, s16 *);
static bool8 UpdateStairWarpIn(s16 *, s16 *, s16 *, s16 *, s16 *);

void palette_bg_faded_fill_white(void)
{
    CpuFastFill16(RGB_WHITE, gPlttBufferFaded, 0x400);
}

void palette_bg_faded_fill_black(void)
{
    CpuFastFill16(RGB_BLACK, gPlttBufferFaded, 0x400);
}

void WarpFadeInScreen(void)
{
    switch (MapTransitionIsExit(GetLastUsedWarpMapType(), GetCurrentMapType()))
    {
    case FALSE:
        palette_bg_faded_fill_black();
        FadeScreen(FADE_FROM_BLACK, 0);
        palette_bg_faded_fill_black();
        break;
    case TRUE:
        palette_bg_faded_fill_white();
        FadeScreen(FADE_FROM_WHITE, 0);
        palette_bg_faded_fill_white();
        break;
    }
}

static void WarpFadeInScreen_Slow(void)
{
    switch (MapTransitionIsExit(GetLastUsedWarpMapType(), GetCurrentMapType()))
    {
    case FALSE:
        palette_bg_faded_fill_black();
        FadeScreen(FADE_FROM_BLACK, 3);
        palette_bg_faded_fill_black();
        break;
    case TRUE:
        palette_bg_faded_fill_white();
        FadeScreen(FADE_FROM_WHITE, 3);
        palette_bg_faded_fill_white();
        break;
    }
}

void FadeInFromBlack(void)
{
    palette_bg_faded_fill_black();
    FadeScreen(FADE_FROM_BLACK, 0);
    palette_bg_faded_fill_black();
}

void WarpFadeOutScreen(void)
{
    const struct MapHeader *header = GetDestinationWarpMapHeader();
    if (header->regionMapSectionId != gMapHeader.regionMapSectionId && MapHasPreviewScreen(header->regionMapSectionId, MPS_TYPE_CAVE))
        FadeScreen(FADE_TO_BLACK, 0);
    else
    {
        switch (MapTransitionIsEnter(GetCurrentMapType(), header->mapType))
        {
        case FALSE:
            FadeScreen(FADE_TO_BLACK, 0);
            break;
        case TRUE:
            FadeScreen(FADE_TO_WHITE, 0);
            break;
        }
    }
}

static void WarpFadeOutScreen_Slow(void)
{
    switch (MapTransitionIsEnter(GetCurrentMapType(), GetDestinationWarpMapHeader()->mapType))
    {
    case FALSE:
        FadeScreen(FADE_TO_BLACK, 3);
        break;
    case TRUE:
        FadeScreen(FADE_TO_WHITE, 3);
        break;
    }
}

static void SetPlayerVisibility(bool8 arg)
{
    SetPlayerInvisibility(!arg);
}

static void ReturnToUnionRoom_WaitFade(u8 taskId)
{
    if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
        DestroyTask(taskId);
}

void FieldCB_ReturnToUnionRoom(void)
{
    ScriptContext2_Enable();
    Overworld_PlaySpecialMapMusic();
    FadeInFromBlack();
    CreateTask(ReturnToUnionRoom_WaitFade, 10);
}

static void FadeTransition_WaitFade(u8 taskId)
{
    if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
    {
        DestroyTask(taskId);
        EnableBothScriptContexts();
    }
}

void FieldCB_ContinueScriptHandleMusic(void)
{
    ScriptContext2_Enable();
    Overworld_PlaySpecialMapMusic();
    FadeInFromBlack();
    CreateTask(FadeTransition_WaitFade, 10);
}

void FieldCB_ContinueScript(void)
{
    ScriptContext2_Enable();
    FadeInFromBlack();
    CreateTask(FadeTransition_WaitFade, 10);
}

static void Task_ReturnToFieldCableLink(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        task->data[1] = CreateTask_ReestablishLinkInCableClubRoom();
        task->data[0]++;
        break;
    case 1:
        if (gTasks[task->data[1]].isActive != TRUE)
        {
            WarpFadeInScreen();
            task->data[0]++;
        }
        break;
    case 2:
        if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
        {
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}

void FieldCB_ReturnToFieldCableLink(void)
{
    ScriptContext2_Enable();
    Overworld_PlaySpecialMapMusic();
    palette_bg_faded_fill_black();
    CreateTask(Task_ReturnToFieldCableLink, 10);
}

static void Task_ReturnToFieldWirelessLink(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        SetLinkStandbyCallback();
        task->data[0]++;
        break;
    case 1:
        if (IsLinkTaskFinished())
        {
            WarpFadeInScreen();
            task->data[0]++;
        }
        break;
    case 2:
        if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
        {
            sub_8009FE8();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}

void FieldCB_ReturnToFieldWirelessLink(void)
{
    ScriptContext2_Enable();
    Overworld_PlaySpecialMapMusic();
    palette_bg_faded_fill_black();
    CreateTask(Task_ReturnToFieldWirelessLink, 10);
}

static void FieldCBSub_OnWarpExit(bool8 fadeFromBlack)
{
    s16 x, y;
    u32 behavior;
    TaskFunc func;

    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);
    if (MetatileBehavior_IsWarpDoor_2(behavior) == TRUE)
    {
        func = Task_OpenHingedDoor;
        switch (MapTransitionIsExit(GetLastUsedWarpMapType(), GetCurrentMapType()))
        {
        case 0:
            palette_bg_faded_fill_black();
            break;
        case 1:
            palette_bg_faded_fill_white();
            break;
        }
    }
    else
    {
        DoWarpDoorFadeIn(fadeFromBlack);
        if (MetatileBehavior_IsNonAnimDoor(behavior) == TRUE)
            func = Task_ExitNonAnimDoor;
        else if (MetatileBehavior_IsDirectionalStairWarp(behavior) == TRUE)
            func = !gLoadingMapOnQuestLog ? Task_WarpIntoMapAnim_DirectionalStairs : Task_WarpIntoMapAnim_Generic;
        else
            func = Task_WarpIntoMapAnim_Generic;
    }
    gLoadingMapOnQuestLog = FALSE;
    CreateTask(func, 10);
}

static void DoWarpDoorFadeIn(bool8 fadeFromBlack)
{
    if (!fadeFromBlack)
        WarpFadeInScreen();
    else
        FadeInFromBlack();
}

void FieldCB_DefaultWarpExit(void)
{
    Overworld_PlaySpecialMapMusic();
    QuestLog_DrawPreviouslyOnQuestHeaderIfInPlaybackMode();
    FieldCBSub_OnWarpExit(FALSE);
    ScriptContext2_Enable();
}

void FieldCB_WarpExitFadeFromBlack(void)
{
    Overworld_PlaySpecialMapMusic();
    QuestLog_DrawPreviouslyOnQuestHeaderIfInPlaybackMode();
    FieldCBSub_OnWarpExit(TRUE);
    ScriptContext2_Enable();
}

static void FieldCB_TeleportWarpIn(void)
{
    Overworld_PlaySpecialMapMusic();
    WarpFadeInScreen();
    QuestLog_DrawPreviouslyOnQuestHeaderIfInPlaybackMode();
    PlaySE(SE_WARP_OUT);
    CreateTask(Task_TeleportWarpIn, 10);
    ScriptContext2_Enable();
}

static void Task_OpenHingedDoor(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    s16 *x = &task->data[2];
    s16 *y = &task->data[3];

    if (task->data[0] == 0)
        task->data[0] = 5;

    switch (task->data[0])
    {
    case 0: // Never reached
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        PlayerGetDestCoords(x, y);
        FieldSetDoorOpened(*x, *y);
        task->data[0] = 1;
        break;
    case 5:
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        DoOutwardBarnDoorWipe();
        WarpFadeInScreen_Slow();
        task->data[0] = 6;
        break;
    case 6:
        task->data[15]++;
        if (task->data[15] == 25)
        {
            PlayerGetDestCoords(x, y);
            PlaySE(GetDoorSoundEffect(*x, *y));
            FieldAnimateDoorOpen(*x, *y);
            task->data[0] = 7;
        }
        break;
    case 7:
        if (!FieldIsDoorAnimationRunning())
        {
            PlayerGetDestCoords(&task->data[12], &task->data[13]);
            SetPlayerVisibility(TRUE);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], MOVEMENT_ACTION_WALK_NORMAL_DOWN);
            task->data[0] = 8;
        }
        break;
    case 8:
        task->data[14]++;
        if (task->data[14] == 14)
        {
            FieldAnimateDoorClose(task->data[12], task->data[13]);
            task->data[0] = 9;
        }
        break;
    case 9:
        if (FieldFadeTransitionBackgroundEffectIsFinished() && walkrun_is_standing_still() && !FieldIsDoorAnimationRunning() && !FuncIsActiveTask(Task_BarnDoorWipe))
        {
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            task->data[0] = 4;
        }
        break;
    // Legacy RS
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished())
        {
            SetPlayerVisibility(TRUE);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], MOVEMENT_ACTION_WALK_NORMAL_DOWN);
            task->data[0] = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            task->data[1] = FieldAnimateDoorClose(*x, *y);
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            task->data[0] = 3;
        }
        break;
    case 3:
        if (task->data[1] < 0 || gTasks[task->data[1]].isActive != TRUE)
            task->data[0] = 4;
        break;
    case 4:
        UnfreezeObjectEvents();
        ScriptContext2_Disable();
        DestroyTask(taskId);
        break;
    }
}

static void Task_ExitNonAnimDoor(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    s16 *x = &task->data[2];
    s16 *y = &task->data[3];

    switch (task->data[0])
    {
    case 0:
        SetPlayerVisibility(FALSE);
        FreezeObjectEvents();
        PlayerGetDestCoords(x, y);
        task->data[0] = 1;
        break;
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished())
        {
            SetPlayerVisibility(TRUE);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], GetWalkNormalMovementAction(GetPlayerFacingDirection()));
            task->data[0] = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            task->data[0] = 3;
        }
        break;
    case 3:
        UnfreezeObjectEvents();
        ScriptContext2_Disable();
        DestroyTask(taskId);
        break;
    }
}

static void Task_WarpIntoMapAnim_Generic(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        gTasks[taskId].data[0]++;
        break;
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished())
        {
            UnfreezeObjectEvents();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}

static void Task_TeleportWarpIn(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        StartTeleportInPlayerAnim();
        gTasks[taskId].data[0]++;
        break;
    case 1:
        if (FieldFadeTransitionBackgroundEffectIsFinished() && WaitTeleportInPlayerAnim() != TRUE)
        {
            UnfreezeObjectEvents();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    }
}

static void Task_WaitFadeAndCreateStartMenuTask(u8 taskId)
{
    if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
    {
        DestroyTask(taskId);
        CreateTask(Task_StartMenuHandleInput, 80);
    }
}

void FadeTransition_FadeInOnReturnToStartMenu(void)
{
    FadeInFromBlack();
    CreateTask(Task_WaitFadeAndCreateStartMenuTask, 80);
    ScriptContext2_Enable();
}

bool8 FieldCB_ReturnToFieldOpenStartMenu(void)
{
    SetUpReturnToStartMenu();
    return FALSE;
}

static void Task_SafariZoneRanOutOfBalls(u8 taskId)
{
    if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
    {
        ScriptContext2_Disable();
        DestroyTask(taskId);
        ClearPlayerHeldMovementAndUnfreezeObjectEvents();
    }
}

void FieldCB_SafariZoneRanOutOfBalls(void)
{
    ScriptContext2_Enable();
    Overworld_PlaySpecialMapMusic();
    FadeInFromBlack();
    CreateTask(Task_SafariZoneRanOutOfBalls, 10);
}

static bool32 WaitWarpFadeOutScreen(void)
{
    return gPaletteFade.active;
}

bool32 FieldFadeTransitionBackgroundEffectIsFinished(void)
{
    if (IsWeatherNotFadingIn() == TRUE && ForestMapPreviewScreenIsRunning())
        return TRUE;
    else
        return FALSE;
}

void DoWarp(void)
{
    ScriptContext2_Enable();
    TryFadeOutOldMapMusic();
    WarpFadeOutScreen();
    PlayRainStoppingSoundEffect();
    PlaySE(SE_EXIT);
    gFieldCallback = FieldCB_DefaultWarpExit;
    CreateTask(Task_Teleport2Warp, 10);
}

void DoDiveWarp(void)
{
    ScriptContext2_Enable();
    TryFadeOutOldMapMusic();
    WarpFadeOutScreen();
    PlayRainStoppingSoundEffect();
    gFieldCallback = FieldCB_DefaultWarpExit;
    CreateTask(Task_Teleport2Warp, 10);
}

void DoStairWarp(u16 metatileBehavior, u16 delay)
{
    u8 taskId = CreateTask(Task_StairWarp, 10);
    gTasks[taskId].data[1] = metatileBehavior;
    gTasks[taskId].data[15] = delay;
    Task_StairWarp(taskId);
}

void DoDoorWarp(void)
{
    ScriptContext2_Enable();
    gFieldCallback = FieldCB_DefaultWarpExit;
    CreateTask(Task_DoorWarp, 10);
}

void DoTeleport2Warp(void)
{
    ScriptContext2_Enable();
    CreateTask(Task_Teleport2Warp, 10);
    gFieldCallback = FieldCB_TeleportWarpIn;
}

void DoUnionRoomWarp(void)
{
    ScriptContext2_Enable();
    gFieldCallback = FieldCB_DefaultWarpExit;
    CreateTask(Task_TeleportWarp, 10);
}

void DoFallWarp(void)
{
    DoDiveWarp();
    gFieldCallback = FieldCB_FallWarpExit;
}

void DoEscalatorWarp(u8 metatileBehavior)
{
    ScriptContext2_Enable();
    StartEscalatorWarp(metatileBehavior, 10);
}

void DoLavaridgeGymB1FWarp(void)
{
    ScriptContext2_Enable();
    StartLavaridgeGymB1FWarp(10);
}

void DoLavaridgeGym1FWarp(void)
{
    ScriptContext2_Enable();
    StartLavaridgeGym1FWarp(10);
}

void DoTeleportWarp(void)
{
    ScriptContext2_Enable();
    TryFadeOutOldMapMusic();
    CreateTask(Task_TeleportWarp, 10);
    gFieldCallback = FieldCB_TeleportWarpIn;
}

void FadeOutAndDoTeleport2Warp(void)
{
    ScriptContext2_Enable();
    WarpFadeOutScreen();
    CreateTask(Task_Teleport2Warp, 10);
    gFieldCallback = FieldCB_Dummy;
}

static void Task_CableClubWarp(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        ScriptContext2_Enable();
        task->data[0]++;
        break;
    case 1:
        if (!WaitWarpFadeOutScreen() && BGMusicStopped())
            task->data[0]++;
        break;
    case 2:
        WarpIntoMap();
        SetMainCallback2(CB2_ReturnToFieldCableClub);
        DestroyTask(taskId);
        break;
    }
}

void DoCableClubWarp(void)
{
    ScriptContext2_Enable();
    TryFadeOutOldMapMusic();
    WarpFadeOutScreen();
    PlaySE(SE_EXIT);
    CreateTask(Task_CableClubWarp, 10);
}

static void Task_ReturnFromLinkRoomWarp(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    switch (data[0])
    {
    case 0:
        ClearLinkCallback_2();
        FadeScreen(FADE_TO_BLACK, 0);
        TryFadeOutOldMapMusic();
        PlaySE(SE_EXIT);
        data[0]++;
        break;
    case 1:
        if (!WaitWarpFadeOutScreen() && BGMusicStopped())
        {
            SetCloseLinkCallback();
            data[0]++;
        }
        break;
    case 2:
        if (!gReceivedRemoteLinkPlayers)
        {
            WarpIntoMap();
            SetMainCallback2(CB2_LoadMap);
            DestroyTask(taskId);
        }
        break;
    }
}

void ReturnFromLinkRoom(void)
{
    CreateTask(Task_ReturnFromLinkRoomWarp, 10);
}

static void Task_Teleport2Warp(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        task->data[0]++;
        break;
    case 1:
        if (!WaitWarpFadeOutScreen() && BGMusicStopped())
            task->data[0]++;
        break;
    case 2:
        WarpIntoMap();
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(taskId);
        break;
    }
}

static void Task_TeleportWarp(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    switch (task->data[0])
    {
    case 0:
        FreezeObjectEvents();
        ScriptContext2_Enable();
        PlaySE(SE_WARP_IN);
        StartTeleportWarpOutPlayerAnim();
        task->data[0]++;
        break;
    case 1:
        if (!WaitTeleportWarpOutPlayerAnim())
        {
            WarpFadeOutScreen();
            task->data[0]++;
        }
        break;
    case 2:
        if (!WaitWarpFadeOutScreen() && BGMusicStopped())
            task->data[0]++;
        break;
    case 3:
        WarpIntoMap();
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(taskId);
        break;
    }
}

static void Task_DoorWarp(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s16 * xp = &task->data[2];
    s16 * yp = &task->data[3];
    switch (task->data[0])
    {
    case 0:
        FreezeObjectEvents();
        PlayerGetDestCoords(xp, yp);
        PlaySE(GetDoorSoundEffect(*xp, *yp - 1));
        task->data[1] = FieldAnimateDoorOpen(*xp, *yp - 1);
        task->data[0] = 1;
        break;
    case 1:
        if (task->data[1] < 0 || gTasks[task->data[1]].isActive != TRUE)
        {
            ObjectEventClearHeldMovementIfActive(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            ObjectEventSetHeldMovement(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)], MOVEMENT_ACTION_WALK_NORMAL_UP);
            task->data[0] = 2;
        }
        break;
    case 2:
        if (walkrun_is_standing_still())
        {
            task->data[1] = FieldAnimateDoorClose(*xp, *yp - 1);
            ObjectEventClearHeldMovementIfFinished(&gObjectEvents[GetObjectEventIdByLocalIdAndMap(OBJ_EVENT_ID_PLAYER, 0, 0)]);
            SetPlayerVisibility(FALSE);
            task->data[0] = 3;
        }
        break;
    case 3:
        if (task->data[1] < 0 || gTasks[task->data[1]].isActive != TRUE)
        {
            task->data[0] = 4;
        }
        break;
    case 4:
        TryFadeOutOldMapMusic();
        WarpFadeOutScreen();
        PlayRainStoppingSoundEffect();
        task->data[0] = 0;
        task->func = Task_Teleport2Warp;
        break;
    case 5:
        TryFadeOutOldMapMusic();
        PlayRainStoppingSoundEffect();
        task->data[0] = 0;
        task->func = Task_Teleport2Warp;
        break;
    }
}

static void Task_StairWarp(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    struct ObjectEvent *playerObj = &gObjectEvents[gPlayerAvatar.objectEventId];
    struct Sprite *playerSpr = &gSprites[gPlayerAvatar.spriteId];
    switch (data[0])
    {
    case 0:
        ScriptContext2_Enable();
        FreezeObjectEvents();
        CameraObjectReset2();
        data[0]++;
        break;
    case 1:
        if (!ObjectEventIsMovementOverridden(playerObj) || ObjectEventClearHeldMovementIfFinished(playerObj))
        {
            if (data[15] != 0)
                data[15]--;
            else
            {
                TryFadeOutOldMapMusic();
                PlayRainStoppingSoundEffect();
                playerSpr->oam.priority = 1;
                InitStairWarpOut(data[1], &data[2], &data[3]);
                PlaySE(SE_EXIT);
                data[0]++;
            }
        }
        break;
    case 2:
        UpdateStairWarpOut(data[2], data[3], &data[4], &data[5], &data[6]);
        data[15]++;
        if (data[15] >= 12)
        {
            WarpFadeOutScreen();
            data[0]++;
        }
        break;
    case 3:
        UpdateStairWarpOut(data[2], data[3], &data[4], &data[5], &data[6]);
        if (!WaitWarpFadeOutScreen() && BGMusicStopped())
            data[0]++;
        break;
    default:
        gFieldCallback = FieldCB_DefaultWarpExit;
        WarpIntoMap();
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(taskId);
        break;
    }
}

static void UpdateStairWarpOut(s16 pXspeed, s16 pYspeed, s16 *pX, s16 *pY, s16 *pTimer)
{
    struct Sprite *playerSpr = &gSprites[gPlayerAvatar.spriteId];
    struct ObjectEvent *playerObj = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (pYspeed > 0 || *pTimer > 6)
        *pY += pYspeed;
    *pX += pXspeed;
    (*pTimer)++;
    playerSpr->pos2.x = *pX >> 5;
    playerSpr->pos2.y = *pY >> 5;
    if (playerObj->heldMovementFinished)
    {
        ObjectEventForceSetHeldMovement(playerObj, GetWalkInPlaceNormalMovementAction(GetPlayerFacingDirection()));
    }
}

static void InitStairWarpOut(u16 metatileBehavior, s16 *pXspeed, s16 *pYspeed)
{
    ObjectEventForceSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], GetWalkInPlaceNormalMovementAction(GetPlayerFacingDirection()));
    GetStairSpeedVecByMetatileBehavior(metatileBehavior, pXspeed, pYspeed);
}

static void GetStairSpeedVecByMetatileBehavior(u8 metatileBehavior, s16 *pXspeed, s16 *pYspeed)
{
    if (MetatileBehavior_IsDirectionalUpRightStairWarp(metatileBehavior))
    {
        *pXspeed = 16;
        *pYspeed = -10;
    }
    else if (MetatileBehavior_IsDirectionalUpLeftStairWarp(metatileBehavior))
    {
        *pXspeed = -17;
        *pYspeed = -10;
    }
    else if (MetatileBehavior_IsDirectionalDownRightStairWarp(metatileBehavior))
    {
        *pXspeed = 17;
        *pYspeed = 3;
    }
    else if (MetatileBehavior_IsDirectionalDownLeftStairWarp(metatileBehavior))
    {
        *pXspeed = -17;
        *pYspeed = 3;
    }
    else
    {
        *pXspeed = 0;
        *pYspeed = 0;
    }
}

static void Task_WarpIntoMapAnim_DirectionalStairs(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    switch (data[0])
    {
    default:
        if (FieldFadeTransitionBackgroundEffectIsFinished() == TRUE)
        {
            CameraObjectReset1();
            ScriptContext2_Disable();
            DestroyTask(taskId);
        }
        break;
    case 0:
        Overworld_PlaySpecialMapMusic();
        WarpFadeInScreen();
        ScriptContext2_Enable();
        InitStairWarpIn(&data[1], &data[2], &data[3], &data[4], &data[5]);
        data[0]++;
        break;
    case 1:
        if (!UpdateStairWarpIn(&data[1], &data[2], &data[3], &data[4], &data[5]))
            data[0]++;
        break;
    }
}

static void InitStairWarpIn(s16 *pXspeed, s16 *pYspeed, s16 *pX, s16 *pY, s16 *a4)
{
    s16 x, y;
    u8 behavior;
    s32 direction;
    struct Sprite *sprite;
    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);
    if (MetatileBehavior_IsDirectionalDownRightStairWarp(behavior) || MetatileBehavior_IsDirectionalUpRightStairWarp(behavior))
        direction = DIR_WEST;
    else
        direction = DIR_EAST;
    ObjectEventForceSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], GetWalkInPlaceSlowMovementAction(direction));
    GetStairSpeedVecByMetatileBehavior(behavior, pXspeed, pYspeed);
    *pX = *pXspeed * 16;
    *pY = *pYspeed * 16;
    *a4 = 16;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = *pX >> 5;
    sprite->pos2.y = *pY >> 5;
    *pXspeed *= -1;
    *pYspeed *= -1;
}

static bool8 UpdateStairWarpIn(s16 *pXspeed, s16 *pYspeed, s16 *pX, s16 *pY, s16 *pTimer)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    if (*pTimer != 0)
    {
        *pX += *pXspeed;
        *pY += *pYspeed;
        sprite->pos2.x = *pX >> 5;
        sprite->pos2.y = *pY >> 5;
        (*pTimer)--;
        return TRUE;
    }
    else
    {
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        return FALSE;
    }
}
