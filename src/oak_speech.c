#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "task.h"
#include "blend_palette.h"
#include "text_window.h"
#include "menu.h"
#include "help_system.h"
#include "new_menu_helpers.h"
#include "event_scripts.h"
#include "scanline_effect.h"
#include "pokeball.h"
#include "naming_screen.h"
#include "math_util.h"
#include "overworld.h"
#include "random.h"
#include "data.h"
#include "speedchoice.h"
#include "constants/songs.h"

#define TAG_GRASS_PLATFORM  0x1000
#define TAG_PIKA_1          0x1001
#define TAG_PIKA_2          0x1002
#define TAG_PIKA_EYES       0x1003

#define LOAD_PIKA     0
#define LOAD_PLATFORM 1

struct OakSpeechResources
{
    void * solidColorsGfx;
    void * trainerPicTilemapBuffer;
//    void * unk_0008;
    u8 filler_000C[4];
    u16 nameWho;
    u16 helpPage;
    u16 windows[4];
    u8 textColor[3];
    u8 textSpeed;
    u8 filler_0020[0x1800];
    u8 bg2TilemapBuffer[0x400];
    u8 bg1TilemapBuffer[0x800];
}; //size=0x2420

EWRAM_DATA struct OakSpeechResources * sOakSpeechResources = NULL;

void Task_OaksSpeech1(u8 taskId);
static void CreateHelpDocsPage1(void);
static void Task_OaksSpeech2(u8 taskId);
static void Task_OakSpeech3(u8 taskId);
void Task_OakSpeech5(u8 taskId);
static void Task_OakSpeech6(u8 taskId);
static void Task_OakSpeech7(u8 taskId);
static void Task_OakSpeech8(u8 taskId);
void Task_OakSpeech9(u8 taskId);
static void Task_OakSpeech10(u8 taskId);
static void Task_OakSpeech10(u8 taskId);
static void Task_OakSpeech11(u8 taskId);
static void Task_OakSpeech12(u8 taskId);
static void Task_OakSpeech13(u8 taskId);
static void Task_OakSpeech14(u8 taskId);
static void Task_OakSpeech15(u8 taskId);
static void Task_OakSpeech16(u8 taskId);
static void Task_OakSpeech17(u8 taskId);
static void Task_OakSpeech18(u8 taskId);
static void Task_OakSpeech19(u8 taskId);
static void Task_OakSpeech20(u8 taskId);
static void Task_OakSpeech21(u8 taskId);
static void Task_OakSpeech22(u8 taskId);
static void Task_OakSpeech23(u8 taskId);
static void Task_OakSpeech24(u8 taskId);
static void Task_OakSpeech29(u8 taskId);
static void Task_OakSpeech25(u8 taskId);
static void Task_OakSpeech26(u8 taskId);
static void Task_OakSpeech27(u8 taskId);
static void Task_OakSpeech30(u8 taskId);
static void Task_OakSpeech31(u8 taskId);
static void Task_OakSpeech32(u8 taskId);
static void Task_OakSpeech34(u8 taskId);
static void Task_OakSpeech33(u8 taskId);
static void Task_OakSpeech36(u8 taskId);
static void Task_OakSpeech37(u8 taskId);
static void Task_OakSpeech38(u8 taskId);
static void Task_OakSpeech38_3(u8 taskId);
static void Task_OakSpeech39(u8 taskId);
static void Task_OakSpeech38_1(u8 taskId);
static void Task_OakSpeech38_sub1(u8 taskId);
static void Task_OakSpeech38_2(u8 taskId);
static void Task_OakSpeech38_sub2(u8 taskId);
static void Task_OakSpeech40(u8 taskId);
static void Task_OakSpeech41(u8 taskId);
static void Task_OakSpeech42(u8 taskId);

static void CB2_ReturnFromNamingScreen(void);
static void CreateNidoranFSprite(u8 taskId);
static void CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(u8 taskId, u8 state);
static void DestroyLinkedPikaOrGrassPlatformSprites(u8 taskId, u8 state);
static void LoadOaksSpeechTrainerPic(u16 whichPic, u16 tileOffset);
static void DestroyOaksSpeechTrainerPic(void);
static void CreateFadeInTask(u8 taskId, u8 state);
static void CreateFadeOutTask(u8 taskId, u8 state);
static void PrintNameChoiceOptions(u8 taskId, u8 state);
static void GetDefaultName(u8 playerOrRival, u8 namePick);

extern const u8 gText_Controls[];
extern const u8 gText_ABUTTONNext[];
extern const u8 gText_ABUTTONNext_BBUTTONBack[];
extern const u8 gText_Boy[];
extern const u8 gText_Girl[];

ALIGNED(4) const u16 sHelpDocsPalette[] = INCBIN_U16("graphics/oak_speech/help_docs_palette.gbapal");
static const u32 sOakSpeechGfx_GameStartHelpUI[] = INCBIN_U32("graphics/oak_speech/game_start_help_ui.4bpp.lz");
static const u32 sNewGameAdventureIntroTilemap[] = INCBIN_U32("graphics/oak_speech/new_game_adventure_intro_tilemap.bin.lz");
static const u32 sOakSpeechGfx_SolidColors[] = INCBIN_U32("graphics/oak_speech/solid_colors.4bpp.lz");
static const u32 sOakSpeech_BackgroundTilemap[] = INCBIN_U32("graphics/oak_speech/background_tilemap.bin.lz");
static const u16 sHelpDocsPage2Tilemap[] = INCBIN_U16("graphics/oak_speech/help_docs_page2_tilemap.bin");
static const u16 sHelpDocsPage3Tilemap[] = INCBIN_U16("graphics/oak_speech/help_docs_page3_tilemap.bin");
static const u16 sOakSpeechGfx_LeafPal[] = INCBIN_U16("graphics/oak_speech/leaf_pal.gbapal");
static const u32 sOakSpeechGfx_LeafPic[] = INCBIN_U32("graphics/oak_speech/leaf_pic.8bpp.lz");
static const u16 sOakSpeechGfx_RedPal[] = INCBIN_U16("graphics/oak_speech/red_pal.gbapal");
static const u32 sOakSpeechGfx_RedPic[] = INCBIN_U32("graphics/oak_speech/red_pic.8bpp.lz");
static const u16 sOakSpeechGfx_OakPal[] = INCBIN_U16("graphics/oak_speech/oak_pal.gbapal");
static const u32 sOakSpeechGfx_OakPic[] = INCBIN_U32("graphics/oak_speech/oak_pic.8bpp.lz");
static const u16 sOakSpeechGfx_RivalPal[] = INCBIN_U16("graphics/oak_speech/rival_pal.gbapal");
static const u32 sOakSpeechGfx_RivalPic[] = INCBIN_U32("graphics/oak_speech/rival_pic.8bpp.lz");
static const u16 sOakSpeech_GrassPlatformPalette[] = INCBIN_U16("graphics/oak_speech/grass_platform_palette.gbapal");
static const u16 sOakSpeech_PikaPalette[] = INCBIN_U16("graphics/oak_speech/pika_palette.gbapal");
static const u32 sOakSpeechGfx_GrassPlatform[] = INCBIN_U32("graphics/oak_speech/grass_platform.4bpp.lz");
static const u32 sOakSpeechGfx_Pika1[] = INCBIN_U32("graphics/oak_speech/pika1.4bpp.lz");
static const u32 sOakSpeechGfx_Pika2[] = INCBIN_U32("graphics/oak_speech/pika2.4bpp.lz");
static const u32 sOakSpeechGfx_PikaEyes[] = INCBIN_U32("graphics/oak_speech/pika_eyes.4bpp.lz");

static const struct BgTemplate sBgTemplates[3] = {
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x000
    }, {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 1,
        .paletteMode = 1,
        .priority = 1,
        .baseTile = 0x000
    }
};

static const struct WindowTemplate sHelpDocsWindowTemplates1[] = {
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 7,
        .width = 30,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x001
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sHelpDocsWindowTemplates2[] = {
    {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 3,
        .width = 24,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x001
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 10,
        .width = 18,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x092
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 24,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x0f3
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sHelpDocsWindowTemplates3[] = {
    {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 3,
        .width = 24,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x001
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 8,
        .width = 24,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x062
    }, {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 13,
        .width = 24,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x0c3
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate *const sHelpDocsWindowTemplatePtrs[3] = {
    sHelpDocsWindowTemplates1,
    sHelpDocsWindowTemplates2,
    sHelpDocsWindowTemplates3
};

static const struct WindowTemplate sNewGameAdventureIntroWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 4,
        .width = 28,
        .height = 15,
        .paletteNum = 15,
        .baseBlock = 0x001
    }, {
        .bg = 0,
        .tilemapLeft = 18,
        .tilemapTop = 9,
        .width = 9,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x174
    }, {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x180
    }, {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 2,
        .width = 12,
        .height = 10,
        .paletteNum = 15,
        .baseBlock = 0x001
    }, DUMMY_WIN_TEMPLATE
};

static const u8 sTextColor_HelpSystem[4] = {
    TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY
};

static const u8 sTextColor_OakSpeech[4] = {
    TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY
};

static const u8 *const sNewGameAdventureIntroTextPointers[] = {
    gNewGameAdventureIntro1,
    gNewGameAdventureIntro2,
    gNewGameAdventureIntro3
};

static const struct CompressedSpriteSheet sOakSpeech_PikaSpriteSheets[3] = {
    { (const void *)sOakSpeechGfx_Pika1, 0x0400, TAG_PIKA_1 },
    { (const void *)sOakSpeechGfx_Pika2, 0x0200, TAG_PIKA_2 },
    { (const void *)sOakSpeechGfx_PikaEyes, 0x0080, TAG_PIKA_EYES },
};

static const struct CompressedSpriteSheet sOakSpeech_GrassPlatformSpriteSheet = {
    (const void *)sOakSpeechGfx_GrassPlatform, 0x0600, TAG_GRASS_PLATFORM
};

static const struct SpritePalette sOakSpeech_PikaSpritePal = {
    (const void *)sOakSpeech_PikaPalette, TAG_PIKA_1
};

static const struct SpritePalette sOakSpeech_GrassPlatformSpritePal = {
    (const void *)sOakSpeech_GrassPlatformPalette, TAG_GRASS_PLATFORM
};

static const union AnimCmd sGrassPlatformAnim1[] = {
    ANIMCMD_FRAME( 0, 0),
    ANIMCMD_END
};

static const union AnimCmd sGrassPlatformAnim2[] = {
    ANIMCMD_FRAME(16, 0),
    ANIMCMD_END
};

static const union AnimCmd sGrassPlatformAnim3[] = {
    ANIMCMD_FRAME(32, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sGrassPlatformAnims1[] = {
    sGrassPlatformAnim1
};
static const union AnimCmd *const sGrassPlatformAnims2[] = {
    sGrassPlatformAnim2
};
static const union AnimCmd *const sGrassPlatformAnims3[] = {
    sGrassPlatformAnim3
};

extern const struct OamData gOamData_AffineOff_ObjBlend_32x32;

static const struct SpriteTemplate sOakSpeech_GrassPlatformSpriteTemplates[3] = {
    { TAG_GRASS_PLATFORM, TAG_GRASS_PLATFORM, &gOamData_AffineOff_ObjBlend_32x32, sGrassPlatformAnims1, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { TAG_GRASS_PLATFORM, TAG_GRASS_PLATFORM, &gOamData_AffineOff_ObjBlend_32x32, sGrassPlatformAnims2, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { TAG_GRASS_PLATFORM, TAG_GRASS_PLATFORM, &gOamData_AffineOff_ObjBlend_32x32, sGrassPlatformAnims3, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
};

static const union AnimCmd sPikaAnim1[] = {
    ANIMCMD_FRAME( 0, 30),
    ANIMCMD_FRAME(16, 30),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sPikaAnim2[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sPikaAnim3[] = {
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0,  8),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(0, 60),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_FRAME(0,  8),
    ANIMCMD_FRAME(2,  8),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sPikaAnims1[] = {
    sPikaAnim1
};
static const union AnimCmd *const sPikaAnims2[] = {
    sPikaAnim2
};
static const union AnimCmd *const sPikaAnims3[] = {
    sPikaAnim3
};

extern const struct OamData gOamData_AffineOff_ObjNormal_32x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x8;

static const struct SpriteTemplate sOakSpeech_PikaSpriteTemplates[3] = {
    { TAG_PIKA_1, TAG_PIKA_1, &gOamData_AffineOff_ObjNormal_32x32, sPikaAnims1, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { TAG_PIKA_2, TAG_PIKA_1, &gOamData_AffineOff_ObjNormal_32x16, sPikaAnims2, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy },
    { TAG_PIKA_EYES, TAG_PIKA_1, &gOamData_AffineOff_ObjNormal_16x8, sPikaAnims3, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy }
};

static const u8 *const sHelpDocsPtrs[] = {
    gNewGame_HelpDocs2, gNewGame_HelpDocs3, gNewGame_HelpDocs4,
    gNewGame_HelpDocs5, gNewGame_HelpDocs6, gNewGame_HelpDocs7
};

const u8 *const gMalePresetNames[] = {
#if defined(FIRERED)
    gNameChoice_Red,
    gNameChoice_Fire,
    gNameChoice_Ash,
    gNameChoice_Kene,
    gNameChoice_Geki,
#elif defined(LEAFGREEN)
    gNameChoice_Green,
    gNameChoice_Leaf,
    gNameChoice_Gary,
    gNameChoice_Kaz,
    gNameChoice_Toru,
#endif
    gNameChoice_Jak,
    gNameChoice_Janne,
    gNameChoice_Jonn,
    gNameChoice_Kamon,
    gNameChoice_Karl,
    gNameChoice_Taylor,
    gNameChoice_Oscar,
    gNameChoice_Hiro,
    gNameChoice_Max,
    gNameChoice_Jon,
    gNameChoice_Ralph,
    gNameChoice_Kay,
    gNameChoice_Tosh,
    gNameChoice_Roak
};

const u8 *const gFemalePresetNames[] = {
#if defined(FIRERED)
    gNameChoice_Red,
    gNameChoice_Fire,
#elif defined(LEAFGREEN)
    gNameChoice_Green,
    gNameChoice_Leaf,
#endif
    gNameChoice_Omi,
    gNameChoice_Jodi,
    gNameChoice_Amanda,
    gNameChoice_Hillary,
    gNameChoice_Makey,
    gNameChoice_Michi,
    gNameChoice_Paula,
    gNameChoice_June,
    gNameChoice_Cassie,
    gNameChoice_Rey,
    gNameChoice_Seda,
    gNameChoice_Kiko,
    gNameChoice_Mina,
    gNameChoice_Norie,
    gNameChoice_Sai,
    gNameChoice_Momo,
    gNameChoice_Suzi
};

static const u8 *const sRivalNameChoices[] = {
#if defined(FIRERED)
    gNameChoice_Green,
    gNameChoice_Gary,
    gNameChoice_Kaz,
    gNameChoice_Toru
#elif defined(LEAFGREEN)
    gNameChoice_Red,
    gNameChoice_Ash,
    gNameChoice_Kene,
    gNameChoice_Geki
#endif
};

static void VBlankCB_NewGameOaksSpeech(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_NewGameOaksSpeech(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void CB2_ReturnToNewGameFromSpeedchoice(void);

void StartNewGameScene(void)
{
    gPlttBufferUnfaded[0] = RGB_BLACK;
    gPlttBufferFaded[0]   = RGB_BLACK;
    InitSpeedchoice(CB2_ReturnToNewGameFromSpeedchoice);
}

void CB2_ReturnToNewGameFromSpeedchoice(void)
{
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);
    gPlttBufferUnfaded[0] = 0;
    gPlttBufferFaded[0] = 0;
    FreeAllWindowBuffers();
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    ResetBgs();
    SetMainCallback2(CB2_NewGameOaksSpeech);
    CreateTask(Task_OaksSpeech1, 0);
}

// ====================================
// SPEEDCHOICE CHANGE
// ====================================
// Change: Skip the tutorial messages entirely
void Task_OaksSpeech1(u8 taskId)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        DmaFill16(3, 0, VRAM, VRAM_SIZE);
        DmaFill32(3, 0, OAM, OAM_SIZE);
        DmaFill16(3, 0, PLTT + sizeof(u16), PLTT_SIZE - 2);
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetTempTileDataBuffers();
        SetHelpContext(HELPCONTEXT_NEW_GAME);
        break;
    case 1:
        sOakSpeechResources = AllocZeroed(sizeof(*sOakSpeechResources));
        OakSpeechNidoranFSetup(1, TRUE);
        break;
    case 2:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        break;
    case 3:
        ResetBgsAndClearDma3BusyFlags(FALSE);
        InitBgsFromTemplates(BG_MODE_BG2_AFFINE, sBgTemplates, NELEMS(sBgTemplates));
        SetBgTilemapBuffer(1, sOakSpeechResources->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sOakSpeechResources->bg2TilemapBuffer);
        ChangeBgX(1, 0, BG_SCROLL_SET);
        ChangeBgY(1, 0, BG_SCROLL_SET);
        ChangeBgX(2, 0, BG_SCROLL_SET);
        ChangeBgY(2, 0, BG_SCROLL_SET);
        gSpriteCoordOffsetX = 0;
        gSpriteCoordOffsetY = 0;
        break;
    case 4:
        gPaletteFade.bufferTransferDisabled = TRUE;
        InitStandardTextBoxWindows();
        ResetBg0();
        Menu_LoadStdPalAt(0xD0);
        LoadPalette(sHelpDocsPalette, 0x000, 0x080);
        LoadPalette(stdpal_get(2) + 15, 0x000, 0x002);
        break;
    case 5:
        sOakSpeechResources->textSpeed = GetTextSpeedSetting();
        gTextFlags.canABSpeedUpPrint = TRUE;
        DecompressAndCopyTileDataToVram(1, sOakSpeechGfx_GameStartHelpUI, 0, 0, 0);
        break;
    case 6:
        if (FreeTempTileDataBuffersIfPossible())
            return;
        ClearDialogWindowAndFrame(0, TRUE);
        FillBgTilemapBufferRect_Palette0(1, 0x0000,  0,  0, 32, 32);
        CopyBgTilemapBufferToVram(1);
        break;
    case 7:
        CreateTopBarWindowLoadPalette(0, 30, 0, 13, 0x1C4);
        FillBgTilemapBufferRect_Palette0(1, 0xD00F,  0,  0, 30, 2);
        FillBgTilemapBufferRect_Palette0(1, 0xD002,  0,  2, 30, 1);
        FillBgTilemapBufferRect_Palette0(1, 0xD00E,  0, 19, 30, 1);
//        CreateHelpDocsPage1();
        gPaletteFade.bufferTransferDisabled = FALSE;
//        gTasks[taskId].data[5] = CreateTextCursorSpriteForOakSpeech(0, 0xE6, 0x95, 0, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        break;
    case 10:
//        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        SetVBlankCallback(VBlankCB_NewGameOaksSpeech);
        gTasks[taskId].data[3] = 80;
        gTasks[taskId].func = Task_OakSpeech9;
        gMain.state = 0;
        return;
    }

    gMain.state++;
}

static void CreateHelpDocsPage1(void)
{
    TopBarWindowPrintTwoStrings(gText_Controls, gText_ABUTTONNext, 0, 0, 1);
    sOakSpeechResources->windows[0] = AddWindow(sHelpDocsWindowTemplatePtrs[sOakSpeechResources->helpPage]);
    PutWindowTilemap(sOakSpeechResources->windows[0]);
    FillWindowPixelBuffer(sOakSpeechResources->windows[0], PIXEL_FILL(0));
    AddTextPrinterParameterized4(sOakSpeechResources->windows[0], 2, 2, 0, 1, 1, sTextColor_HelpSystem, 0, gNewGame_HelpDocs1);
    CopyWindowToVram(sOakSpeechResources->windows[0], COPYWIN_BOTH);
    FillBgTilemapBufferRect_Palette0(1, 0x3000, 1, 3, 5, 16);
    CopyBgTilemapBufferToVram(1);
}

static void Task_OakSpeech4(u8 taskId)
{
    u8 i = 0;
    u8 r7 = sOakSpeechResources->helpPage - 1;
    if (sOakSpeechResources->helpPage == 0)
    {
        CreateHelpDocsPage1();
    }
    else
    {
        TopBarWindowPrintString(gText_ABUTTONNext_BBUTTONBack, 0, TRUE);
        for (i = 0; i < 3; i++)
        {
            sOakSpeechResources->windows[i] = AddWindow(&sHelpDocsWindowTemplatePtrs[sOakSpeechResources->helpPage][i]);
            PutWindowTilemap(sOakSpeechResources->windows[i]);
            FillWindowPixelBuffer(sOakSpeechResources->windows[i], PIXEL_FILL(0));
            AddTextPrinterParameterized4(sOakSpeechResources->windows[i], 2, 6, 0, 1, 1, sTextColor_HelpSystem, 0, sHelpDocsPtrs[i + r7 * 3]);
            CopyWindowToVram(sOakSpeechResources->windows[i], COPYWIN_BOTH);
        }

        if (sOakSpeechResources->helpPage == 1)
        {
            CopyToBgTilemapBufferRect(1, sHelpDocsPage2Tilemap, 1, 3, 5, 16);
        }
        else
        {
            CopyToBgTilemapBufferRect(1, sHelpDocsPage3Tilemap, 1, 3, 5, 16);
        }
        CopyBgTilemapBufferToVram(1);
    }
    BeginNormalPaletteFade(0xFFFFDFFF, -1, 16, 0, stdpal_get(2)[15]);
    gTasks[taskId].func = Task_OakSpeech5;
}

static void Task_OaksSpeech2(u8 taskId)
{
    if (!gPaletteFade.active && JOY_NEW((A_BUTTON | B_BUTTON)))
    {
        if (JOY_NEW(A_BUTTON))
        {
            gTasks[taskId].data[15] = 1;
            if (sOakSpeechResources->helpPage < 2)
            {
                BeginNormalPaletteFade(0xFFFFDFFF, -1, 0, 16, stdpal_get(2)[15]);
            }
        }
        else
        {
            if (sOakSpeechResources->helpPage != 0)
            {
                gTasks[taskId].data[15] = -1;
                BeginNormalPaletteFade(0xFFFFDFFF, -1, 0, 16, stdpal_get(2)[15]);
            }
            else
                return;
        }
    }
    else
        return;
    PlaySE(SE_SELECT);
    gTasks[taskId].func = Task_OakSpeech3;
}

static void Task_OakSpeech3(u8 taskId)
{
    u8 r8 = 0;
    u8 i;

    if (!gPaletteFade.active)
    {
        switch (sOakSpeechResources->helpPage) {
        case 0:
            r8 = 1;
            break;
        case 1:
        case 2:
            r8 = 3;
            break;
        }
        sOakSpeechResources->helpPage += gTasks[taskId].data[15];
        if (sOakSpeechResources->helpPage < 3)
        {
            for (i = 0; i < r8; i++)
            {
                FillWindowPixelBuffer(sOakSpeechResources->windows[i], PIXEL_FILL(0));
                ClearWindowTilemap(sOakSpeechResources->windows[i]);
                CopyWindowToVram(sOakSpeechResources->windows[i], COPYWIN_BOTH);
                RemoveWindow(sOakSpeechResources->windows[i]);
                sOakSpeechResources->windows[i] = 0;
            }
            gTasks[taskId].func = Task_OakSpeech4;
        }
        else
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 2, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_OakSpeech5;
        }
    }
}

void Task_OakSpeech5(u8 taskId)
{
    u8 i = 0;

    if (!gPaletteFade.active)
    {
        for (i = 0; i < 3; i++)
        {
            FillWindowPixelBuffer(sOakSpeechResources->windows[i], PIXEL_FILL(0));
            ClearWindowTilemap(sOakSpeechResources->windows[i]);
            CopyWindowToVram(sOakSpeechResources->windows[i], COPYWIN_BOTH);
            RemoveWindow(sOakSpeechResources->windows[i]);
            sOakSpeechResources->windows[i] = 0;
        }
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 18);
        CopyBgTilemapBufferToVram(1);
        DestroyTextCursorSprite(gTasks[taskId].data[5]);
        sOakSpeechResources->windows[0] = 0;
        LoadPalette(sOakSpeechResources->windows, 0, 2);
        gTasks[taskId].data[3] = 32;
        gTasks[taskId].func = Task_OakSpeech6;
    }
}

static void Task_OakSpeech6(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u32 sp14 = 0;

    if (data[3] != 0)
        data[3]--;
    else
    {
        void * ptr;
        PlayBGM(MUS_NEW_GAME_INTRO);
        ClearTopBarWindow();
        TopBarWindowPrintString(gText_ABUTTONNext, 0, TRUE);
        ptr = MallocAndDecompress(sNewGameAdventureIntroTilemap, &sp14);
        CopyToBgTilemapBufferRect(1, ptr, 0, 2, 30, 19);
        CopyBgTilemapBufferToVram(1);
        Free(ptr);
        ptr = NULL;
        data[14] = AddWindow(&sNewGameAdventureIntroWindowTemplates[0]);
        PutWindowTilemap(data[14]);
        FillWindowPixelBuffer(data[14], PIXEL_FILL(0));
        CopyWindowToVram(data[14], COPYWIN_BOTH);
        sOakSpeechResources->helpPage = 0;
        gMain.state = 0;
        data[15] = 16;
        AddTextPrinterParameterized4(data[14], 2, 3, 5, 1, 0, sTextColor_OakSpeech, 0, sNewGameAdventureIntroTextPointers[0]);
        data[5] = CreateTextCursorSpriteForOakSpeech(0, 0xe2, 0x91, 0, 0);
        gSprites[data[5]].oam.objMode = ST_OAM_OBJ_BLEND;
        gSprites[data[5]].oam.priority = 0;
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, LOAD_PIKA);
        BeginNormalPaletteFade(0xFFFFFFFF, 2, 16, 0, RGB_BLACK);
        gTasks[taskId].func = Task_OakSpeech7;
    }
}

static void Task_OakSpeech7(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    switch (gMain.state)
    {
    case 0:
        if (!gPaletteFade.active)
        {
            SetGpuReg(REG_OFFSET_WIN0H, 0x00F0);
            SetGpuReg(REG_OFFSET_WIN0V, 0x10A0);
            SetGpuReg(REG_OFFSET_WININ, 0x003F);
            SetGpuReg(REG_OFFSET_WINOUT, 0x001F);
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
            gMain.state = 1;
        }
        break;
    case 1:
        if (JOY_NEW((A_BUTTON | B_BUTTON)))
        {
            if (JOY_NEW(A_BUTTON))
            {
                sOakSpeechResources->helpPage++;
            }
            else if (sOakSpeechResources->helpPage != 0)
            {
                sOakSpeechResources->helpPage--;
            }
            else
            {
                break;
            }
            PlaySE(SE_SELECT);
            if (sOakSpeechResources->helpPage == 3)
            {
                gMain.state = 4;
            }
            else
            {
                SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1);
                SetGpuReg(REG_OFFSET_BLDALPHA, (16 - data[15]) | data[15]);
                gMain.state++;
            }
        }
        break;
    case 2:
        data[15] -= 2;
        SetGpuReg(REG_OFFSET_BLDALPHA, ((16 - data[15]) << 8) | data[15]);
        if (data[15] <= 0)
        {
            FillWindowPixelBuffer(data[14], PIXEL_FILL(0));
            AddTextPrinterParameterized4(data[14], 2, 3, 5, 1, 0, sTextColor_OakSpeech, 0, sNewGameAdventureIntroTextPointers[sOakSpeechResources->helpPage]);
            if (sOakSpeechResources->helpPage == 0)
            {
                ClearTopBarWindow();
                TopBarWindowPrintString(gText_ABUTTONNext, 0, TRUE);
            }
            else
            {
                ClearTopBarWindow();
                TopBarWindowPrintString(gText_ABUTTONNext_BBUTTONBack, 0, TRUE);
            }
            gMain.state++;
        }
        break;
    case 3:
        data[15] += 2;
        SetGpuReg(REG_OFFSET_BLDALPHA, ((16 - data[15]) << 8) | data[15]);
        if (data[15] >= 16)
        {
            data[15] = 16;
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            gMain.state = 1;
        }
        break;
    case 4:
        DestroyTextCursorSprite(gTasks[taskId].data[5]);
        PlayBGM(MUS_NEW_GAME_EXIT);
        data[15] = 24;
        gMain.state++;
        break;
    default:
        if (data[15] != 0)
            data[15]--;
        else
        {
            gMain.state = 0;
            sOakSpeechResources->helpPage = 0;
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0);
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
            BeginNormalPaletteFade(0xFFFFFFFF, 2, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_OakSpeech8;
        }
        break;
    }
}

static void Task_OakSpeech8(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        DestroyTopBarWindow();
        FillWindowPixelBuffer(data[14], PIXEL_FILL(0));
        ClearWindowTilemap(data[14]);
        CopyWindowToVram(data[14], COPYWIN_BOTH);
        RemoveWindow(data[14]);
        data[14] = 0;
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(1);
        DestroyLinkedPikaOrGrassPlatformSprites(taskId, LOAD_PIKA);
        data[3] = 80;
        gTasks[taskId].func = Task_OakSpeech9;
    }
}

void Task_OakSpeech9(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u32 size = 0;

    if (data[3] != 0)
        data[3]--;
    else
    {
        sOakSpeechResources->solidColorsGfx = MallocAndDecompress(sOakSpeechGfx_SolidColors, &size);
        LoadBgTiles(1, sOakSpeechResources->solidColorsGfx, size, 0);
        CopyToBgTilemapBuffer(1, sOakSpeech_BackgroundTilemap, 0, 0);
        CopyBgTilemapBufferToVram(1);
        CreateNidoranFSprite(taskId);
        LoadOaksSpeechTrainerPic(3, 0);
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, LOAD_PLATFORM);
        PlayBGM(MUS_ROUTE24);
        BeginNormalPaletteFade(0xFFFFFFFF, 5, 16, 0, RGB_BLACK);
        data[3] = 80;
        ShowBg(2);
        gTasks[taskId].func = Task_OakSpeech10;
    }
}

#define OaksSpeechPrintMessage(str, speed) ({                                                                                        \
    DrawDialogueFrame(0, FALSE);                                                                                                     \
    if (str != gStringVar4)                                                                                                          \
    {                                                                                                                                \
        StringExpandPlaceholders(gStringVar4, str);                                                                                  \
        AddTextPrinterParameterized2(0, 4, gStringVar4, speed, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY); \
    }                                                                                                                                \
    else                                                                                                                             \
    {                                                                                                                                \
        AddTextPrinterParameterized2(0, 4, str, speed, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);         \
    }                                                                                                                                \
    CopyWindowToVram(0, COPYWIN_BOTH);                                                                                               \
})

static void Task_OakSpeech10(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            OaksSpeechPrintMessage(gOakText_WelcomeToTheWorld, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech11;
        }
    }
}

static void Task_OakSpeech11(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        OaksSpeechPrintMessage(gOakText_WorldInhabited1, sOakSpeechResources->textSpeed);
        gTasks[taskId].data[3] = 30;
        gTasks[taskId].func = Task_OakSpeech12;
    }
}

static void Task_OakSpeech12(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u8 spriteId;

    if (!IsTextPrinterActive(0))
    {
        if (data[3] != 0)
            data[3]--;
        // else {
        spriteId = gTasks[taskId].data[4];
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].data[0] = 0;
        CreatePokeballSpriteToReleaseMon(spriteId, gSprites[spriteId].oam.paletteNum, 0x64, 0x42, 0, 0, 32, 0xFFFF1FFF);
        gTasks[taskId].func = Task_OakSpeech13;
        gTasks[taskId].data[3] = 0;
        // }
    }
}

static void Task_OakSpeech13(u8 taskId)
{
    if (IsCryFinished())
    {
        if (gTasks[taskId].data[3] >= 96)
            gTasks[taskId].func = Task_OakSpeech14;
    }
    if (gTasks[taskId].data[3] < 0x4000)
    {
        gTasks[taskId].data[3]++;
        if (gTasks[taskId].data[3] == 32)
        {
            OaksSpeechPrintMessage(gOakText_WorldInhabited2, sOakSpeechResources->textSpeed);
            PlayCry1(SPECIES_NIDORAN_F, 0);
        }
    }
}

static void Task_OakSpeech14(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        OaksSpeechPrintMessage(gOakText_PetsBattlingStudy, sOakSpeechResources->textSpeed);
        gTasks[taskId].func = Task_OakSpeech15;
    }
}

static void Task_OakSpeech15(u8 taskId)
{
    u8 spriteId;

    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, TRUE);
        spriteId = gTasks[taskId].data[4];
        gTasks[taskId].data[6] = CreateTradePokeballSprite(spriteId, gSprites[spriteId].oam.paletteNum, 0x64, 0x42, 0, 0, 32, 0xFFFF1F3F);
        gTasks[taskId].data[3] = 48;
        gTasks[taskId].data[0] = 64;
        gTasks[taskId].func = Task_OakSpeech16;
    }
}

static void Task_OakSpeech16(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[0] != 0)
    {
        if (data[0] < 24)
        {
            gSprites[data[4]].pos1.y--;
        }
        data[0]--;
    }
    else
    {
        if (data[3] == 48)
        {
            DestroySprite(&gSprites[data[4]]);
            DestroySprite(&gSprites[data[6]]);
        }
        if (data[3] != 0)
        {
            data[3]--;
        }
        else
        {
            OaksSpeechPrintMessage(gOakText_TellMeALittleAboutYourself, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech17;
        }
    }
}

// ====================================
// SPEEDCHOICE CHANGE
// ====================================
// Change: Skip naming yourself and rival
static void Task_OakSpeech17(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, TRUE);
        CreateFadeInTask(taskId, 2);
        data[3] = 48;
        gSaveBlock2Ptr->playerGender = FEMALE;
        StringCopy7(gSaveBlock1Ptr->rivalName, sRivalNameChoices[Random() % NELEMS(sRivalNameChoices)]);
        SeedRngAndSetTrainerId();
        gTasks[taskId].func = Task_OakSpeech33;
    }
}

static void Task_OakSpeech18(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            data[1] = -60;
            DestroyOaksSpeechTrainerPic();
            OaksSpeechPrintMessage(gOakText_AskPlayerGender, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech19;
        }
    }
}

static void Task_OakSpeech19(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        gTasks[taskId].data[13] = AddWindow(&sNewGameAdventureIntroWindowTemplates[1]);
        PutWindowTilemap(gTasks[taskId].data[13]);
        DrawStdFrameWithCustomTileAndPalette(gTasks[taskId].data[13], 1, GetStdWindowBaseTileNum(), 14);
        FillWindowPixelBuffer(gTasks[taskId].data[13], PIXEL_FILL(1));
        sOakSpeechResources->textColor[0] = 1;
        sOakSpeechResources->textColor[1] = 2;
        sOakSpeechResources->textColor[2] = 3;
        AddTextPrinterParameterized3(gTasks[taskId].data[13], 2, 8, 1, sOakSpeechResources->textColor, 0, gText_Boy);
        sOakSpeechResources->textColor[0] = 1;
        sOakSpeechResources->textColor[1] = 2;
        sOakSpeechResources->textColor[2] = 3;
        AddTextPrinterParameterized3(gTasks[taskId].data[13], 2, 8, 17, sOakSpeechResources->textColor, 0, gText_Girl);
        Menu_InitCursor(gTasks[taskId].data[13], 2, 0, 1, GetFontAttribute(2, 1) + 2, 2, 0);
        CopyWindowToVram(gTasks[taskId].data[13], COPYWIN_BOTH);
        gTasks[taskId].func = Task_OakSpeech20;
    }
}

static void Task_OakSpeech20(u8 taskId)
{
    s8 input = Menu_ProcessInputNoWrapAround();
    switch (input)
    {
    case 0:
        gSaveBlock2Ptr->playerGender = MALE;
        break;
    case 1:
        gSaveBlock2Ptr->playerGender = FEMALE;
        break;
    case -1:
    case -2:
        return;
    }
    gTasks[taskId].func = Task_OakSpeech21;

}

static void Task_OakSpeech21(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    ClearStdWindowAndFrameToTransparent(data[13], TRUE);
    RemoveWindow(data[13]);
    data[13] = 0;
    ClearDialogWindowAndFrame(0, TRUE);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(0);
    gTasks[taskId].func = Task_OakSpeech22;
}

static void Task_OakSpeech22(u8 taskId)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        LoadOaksSpeechTrainerPic(MALE, 0);
    else
        LoadOaksSpeechTrainerPic(FEMALE, 0);
    CreateFadeOutTask(taskId, 2);
    gTasks[taskId].data[3] = 32;
    gTasks[taskId].func = Task_OakSpeech23;
}

static void Task_OakSpeech23(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        if (data[3] != 0)
            data[3]--;
        else
        {
            data[1] = 0;
            OaksSpeechPrintMessage(gOakText_AskPlayerName, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech24;
        }
    }
}

static void Task_OakSpeech24(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        sOakSpeechResources->nameWho = 0;
        gTasks[taskId].func = Task_OakSpeech25;
    }
}
static void Task_OakSpeech35(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!IsTextPrinterActive(0))
    {
        if (data[1] > -60)
        {
            data[1] -= 2;
            gSpriteCoordOffsetX += 2;
            ChangeBgX(2, 0x200, BG_SCROLL_SUB);
        }
        else
        {
            data[1] = -60;
            PrintNameChoiceOptions(taskId, sOakSpeechResources->nameWho);
            gTasks[taskId].func = Task_OakSpeech29;
        }
    }
}

static void Task_OakSpeech28(u8 taskId)
{
    PrintNameChoiceOptions(taskId, sOakSpeechResources->nameWho);
    if (sOakSpeechResources->nameWho == 0)
    {
        OaksSpeechPrintMessage(gOakText_AskPlayerName, 0);
    }
    else
    {
        OaksSpeechPrintMessage(gOakText_AskRivalName, 0);
    }
    gTasks[taskId].func = Task_OakSpeech29;
}

static void Task_OakSpeech29(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    s8 input = Menu_ProcessInput();
    switch (input)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        PlaySE(SE_SELECT);
        ClearStdWindowAndFrameToTransparent(data[13], TRUE);
        RemoveWindow(data[13]);
        GetDefaultName(sOakSpeechResources->nameWho, input - 1);
        data[15] = 1;
        gTasks[taskId].func = Task_OakSpeech26;
        break;
    case 0:
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_OakSpeech25;
        break;
    case -1:
        break;
    }
}

static void Task_OakSpeech25(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        GetDefaultName(sOakSpeechResources->nameWho, 0);
        if (sOakSpeechResources->nameWho == 0)
        {
            DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, 0, CB2_ReturnFromNamingScreen);
        }
        else
        {
            ClearStdWindowAndFrameToTransparent(gTasks[taskId].data[13], TRUE);
            RemoveWindow(gTasks[taskId].data[13]);
            DoNamingScreen(NAMING_SCREEN_RIVAL, gSaveBlock1Ptr->rivalName, 0, 0, 0, CB2_ReturnFromNamingScreen);
        }
        DestroyLinkedPikaOrGrassPlatformSprites(taskId, LOAD_PLATFORM);
        FreeAllWindowBuffers();
    }
}

static void Task_OakSpeech26(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (data[15] == 1)
        {
            if (sOakSpeechResources->nameWho == 0)
            {
                StringExpandPlaceholders(gStringVar4, gOakText_FinalizePlayerName);
            }
            else
            {
                StringExpandPlaceholders(gStringVar4, gOakText_ConfirmRivalName);
            }
            OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
            data[15] = 0;
            data[3] = 25;
        }
        else if (!IsTextPrinterActive(0))
        {
            if (data[3] != 0)
                data[3]--;
            else
            {
                CreateYesNoMenu(&sNewGameAdventureIntroWindowTemplates[2], 2, 0, 2, GetStdWindowBaseTileNum(), 14, 0);
                gTasks[taskId].func = Task_OakSpeech27;
            }
        }
    }
}

static void Task_OakSpeech27(u8 taskId)
{
    s8 input = Menu_ProcessInputNoWrapClearOnChoose();
    switch (input)
    {
    case 0:
        PlaySE(SE_SELECT);
        gTasks[taskId].data[3] = 40;
        if (sOakSpeechResources->nameWho == 0)
        {
            ClearDialogWindowAndFrame(0, TRUE);
            CreateFadeInTask(taskId, 2);
            gTasks[taskId].func = Task_OakSpeech30;
        }
        else
        {
            StringExpandPlaceholders(gStringVar4, gOakText_RememberRivalName);
            OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
            gTasks[taskId].func = Task_OakSpeech31;
        }
        break;
    case 1:
    case -1:
        PlaySE(SE_SELECT);
        if (sOakSpeechResources->nameWho == 0)
            gTasks[taskId].func = Task_OakSpeech24;
        else
            gTasks[taskId].func = Task_OakSpeech28;
        break;
    }
}

static void Task_OakSpeech30(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        DestroyOaksSpeechTrainerPic();
        if (data[3] != 0)
            data[3]--;
        else
            gTasks[taskId].func = Task_OakSpeech32;
    }
}

static void Task_OakSpeech31(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        ClearDialogWindowAndFrame(0, TRUE);
        CreateFadeInTask(taskId, 2);
        gTasks[taskId].func = Task_OakSpeech33;
    }
}

static void Task_OakSpeech32(u8 taskId)
{
    ChangeBgX(2, 0, BG_SCROLL_SET);
    gTasks[taskId].data[1] = 0;
    gSpriteCoordOffsetX = 0;
    LoadOaksSpeechTrainerPic(2, 0);
    CreateFadeOutTask(taskId, 2);
    gTasks[taskId].func = Task_OakSpeech34;
}

static void Task_OakSpeech34(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        OaksSpeechPrintMessage(gOakText_IntroduceRival, sOakSpeechResources->textSpeed);
        sOakSpeechResources->nameWho = 1;
        gTasks[taskId].func = Task_OakSpeech35;
    }
}

static void Task_OakSpeech33(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (data[2] != 0)
    {
        DestroyOaksSpeechTrainerPic();
        if (data[3] != 0)
            data[3]--;
        else
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
                LoadOaksSpeechTrainerPic(MALE, 0);
            else
                LoadOaksSpeechTrainerPic(FEMALE, 0);
            gTasks[taskId].data[1] = 0;
            gSpriteCoordOffsetX = 0;
            ChangeBgX(2, 0, BG_SCROLL_SET);
            CreateFadeOutTask(taskId, 2);
            gTasks[taskId].func = Task_OakSpeech36;
        }
    }
}

static void Task_OakSpeech36(u8 taskId)
{
    if (gTasks[taskId].data[2] != 0)
    {
        StringExpandPlaceholders(gStringVar4, gOakText_LegendAboutToUnfold);
        OaksSpeechPrintMessage(gStringVar4, sOakSpeechResources->textSpeed);
        gTasks[taskId].data[3] = 30;
        gTasks[taskId].func = Task_OakSpeech37;
    }
}

static void Task_OakSpeech37(u8 taskId)
{
    if (!IsTextPrinterActive(0))
    {
        if (gTasks[taskId].data[3] != 0)
            gTasks[taskId].data[3]--;
        else
        {
            FadeOutBGM(4);
            gTasks[taskId].func = Task_OakSpeech38;
        }
    }
}

static void Task_OakSpeech38(u8 taskId)
{
    sOakSpeechResources->helpPage = 0;
    Task_OakSpeech38_1(taskId);
    Task_OakSpeech38_2(taskId);
    Task_OakSpeech38_3(taskId);
}

static void Task_OakSpeech38_3(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    SetBgAttribute(2, 6, 1);
    data[0] = 0;
    data[1] = 0;
    data[2] = Q_8_8(1);
    data[15] = 0;
    gTasks[taskId].func = Task_OakSpeech39;
}

static void Task_OakSpeech39(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    s16 x, y;
    u16 r0;

    sOakSpeechResources->helpPage++;
    if (sOakSpeechResources->helpPage % 20 == 0)
    {
        if (sOakSpeechResources->helpPage == 40)
            PlaySE(SE_WARP_IN);
        r0 = data[2];
        data[2] -= Q_8_8(0.125);
        x = inv_Q_8_8(r0 - Q_8_8(0.03125));
        y = inv_Q_8_8(data[2] - Q_8_8(0.0625));
        SetBgAffine(2, 0x7800, 0x5400, 0x78, 0x54, x, y, 0);
        if (data[2] <= Q_8_8(0.375))
        {
            data[15] = 1;
            data[0] = 36;
            gTasks[taskId].func = Task_OakSpeech40;
        }
    }
}

static void Task_OakSpeech38_1(u8 taskId)
{
    u8 taskId2 = CreateTask(Task_OakSpeech38_sub1, 1);
    s16 * data = gTasks[taskId2].data;
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[15] = 0;
    BeginNormalPaletteFade(0xFFFF0FCF, 4, 0, 16, RGB_BLACK);
}

static void Task_OakSpeech38_sub1(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        if (data[1] != 0)
        {
            DestroyTask(taskId);
            DestroyLinkedPikaOrGrassPlatformSprites(taskId, LOAD_PLATFORM);
        }
        else
        {
            data[1]++;
            BeginNormalPaletteFade(0x0000F000, 0, 0, 16, RGB_BLACK);
        }
    }
}

static void Task_OakSpeech38_2(u8 taskId)
{
    u8 taskId2 = CreateTask(Task_OakSpeech38_sub2, 2);
    s16 * data = gTasks[taskId2].data;
    data[0] = 8;
    data[1] = 0;
    data[2] = 8;
    data[14] = 0;
    data[15] = 0;
}

static void Task_OakSpeech38_sub2(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u8 i;

    if (data[0] != 0)
        data[0]--;
    else
    {
        if (data[1] <= 0 && data[2] != 0)
            data[2]--;
        BlendPalette(0x40, 0x20, data[14], RGB_WHITE);
        data[14]++;
        data[1]--;
        data[0] = data[2];
        if (data[14] > 14)
        {
            for (i = 0; i < 32; i++)
            {
                gPlttBufferFaded[i + 0x40] = RGB_WHITE;
                gPlttBufferUnfaded[i + 0x40] = RGB_WHITE;
            }
            DestroyTask(taskId);
        }
    }
}

static void Task_OakSpeech40(u8 taskId)
{
    if (gTasks[taskId].data[0] != 0)
        gTasks[taskId].data[0]--;
    else
    {
        BeginNormalPaletteFade(0x00000030, 2, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_OakSpeech41;
    }
}

static void Task_OakSpeech41(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_OakSpeech42;
    }
}

static void Task_OakSpeech42(u8 taskId)
{
    FreeAllWindowBuffers();
    OakSpeechNidoranFFreeResources();
    Free(sOakSpeechResources);
    sOakSpeechResources = NULL;
    gTextFlags.canABSpeedUpPrint = FALSE;
    SetMainCallback2(CB2_NewGame);
    DestroyTask(taskId);
}

static void CB2_ReturnFromNamingScreen(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        DmaFill16(3, 0, VRAM, VRAM_SIZE);
        DmaFill32(3, 0, OAM, OAM_SIZE);
        DmaFill16(3, RGB_BLACK, PLTT + sizeof(u16), PLTT_SIZE - sizeof(u16));
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetTempTileDataBuffers();
        break;
    case 1:
        ResetBgsAndClearDma3BusyFlags(FALSE);
        InitBgsFromTemplates(BG_MODE_BG2_AFFINE, sBgTemplates, NELEMS(sBgTemplates));
        SetBgTilemapBuffer(1, sOakSpeechResources->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sOakSpeechResources->bg2TilemapBuffer);
        ChangeBgX(1, 0, BG_SCROLL_SET);
        ChangeBgY(1, 0, BG_SCROLL_SET);
        ChangeBgX(2, 0, BG_SCROLL_SET);
        ChangeBgY(2, 0, BG_SCROLL_SET);
        break;
    case 2:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        break;
    case 3:
        FreeAllWindowBuffers();
        InitStandardTextBoxWindows();
        ResetBg0();
        LoadPalette(sHelpDocsPalette, 0, 0xe0);
        break;
    case 4:
        DecompressAndCopyTileDataToVram(1, sOakSpeechGfx_SolidColors, 0, 0, 0);
        break;
    case 5:
        if (FreeTempTileDataBuffersIfPossible())
            return;
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        CopyToBgTilemapBuffer(1, sOakSpeech_BackgroundTilemap, 0, 0);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        break;
    case 6:
        taskId = CreateTask(Task_OakSpeech26, 0);
        if (sOakSpeechResources->nameWho == 0)
        {
            if (gSaveBlock2Ptr->playerGender == MALE)
                LoadOaksSpeechTrainerPic(MALE, 0);
            else
                LoadOaksSpeechTrainerPic(FEMALE, 0);
        }
        else
            LoadOaksSpeechTrainerPic(2, 0);
        gTasks[taskId].data[1] = -60;
        gSpriteCoordOffsetX += 60;
        ChangeBgX(2, -0x3C00, BG_SCROLL_SET);
        CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(taskId, LOAD_PLATFORM);
        gTasks[taskId].data[15] = 1;
        break;
    case 7:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetVBlankCallback(VBlankCB_NewGameOaksSpeech);
        gTextFlags.canABSpeedUpPrint = TRUE;
        SetMainCallback2(CB2_NewGameOaksSpeech);
        return;
    }

    gMain.state++;
}

static void CreateNidoranFSprite(u8 taskId)
{
    u8 spriteId;

    DecompressPicFromTable(&gMonFrontPicTable[SPECIES_NIDORAN_F], OakSpeechNidoranFGetBuffer(0), SPECIES_NIDORAN_F);
    LoadCompressedSpritePaletteUsingHeap(&gMonPaletteTable[SPECIES_NIDORAN_F]);
    SetMultiuseSpriteTemplateToPokemon(SPECIES_NIDORAN_F, 0);
    spriteId = CreateSprite(&gMultiuseSpriteTemplate, 0x60, 0x60, 1);
    gSprites[spriteId].callback = SpriteCallbackDummy;
    gSprites[spriteId].oam.priority = 1;
    gSprites[spriteId].invisible = TRUE;
    gTasks[taskId].data[4] = spriteId;
}

static void SpriteCB_PikaSync(struct Sprite * sprite)
{
    sprite->pos2.y = gSprites[sprite->data[0]].animCmdIndex;
}

static void CreatePikaOrGrassPlatformSpriteAndLinkToCurrentTask(u8 taskId, u8 state)
{
    u8 spriteId;
    u8 i = 0;

    switch (state)
    {
    case LOAD_PIKA:
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[0]);
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[1]);
        LoadCompressedSpriteSheet(&sOakSpeech_PikaSpriteSheets[2]);
        LoadSpritePalette(&sOakSpeech_PikaSpritePal);
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[0], 0x10, 0x11, 2);
        gSprites[spriteId].oam.priority = 0;
        gTasks[taskId].data[7] = spriteId;
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[1], 0x10, 0x09, 3);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].data[0] = gTasks[taskId].data[7];
        gSprites[spriteId].callback = SpriteCB_PikaSync;
        gTasks[taskId].data[8] = spriteId;
        spriteId = CreateSprite(&sOakSpeech_PikaSpriteTemplates[2], 0x18, 0x0D, 1);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].data[0] = gTasks[taskId].data[7];
        gSprites[spriteId].callback = SpriteCB_PikaSync;
        gTasks[taskId].data[9] = spriteId;
        break;
    case LOAD_PLATFORM:
        LoadCompressedSpriteSheet(&sOakSpeech_GrassPlatformSpriteSheet);
        LoadSpritePalette(&sOakSpeech_GrassPlatformSpritePal);
        for (i = 0; i < 3; i++)
        {
            spriteId = CreateSprite(&sOakSpeech_GrassPlatformSpriteTemplates[i], i * 32 + 88, 0x70, 1);
            gSprites[spriteId].oam.priority = 2;
            gSprites[spriteId].animPaused = TRUE;
            gSprites[spriteId].coordOffsetEnabled = TRUE;
            gTasks[taskId].data[7 + i] = spriteId;
        }
        break;
    }
}

static void DestroyLinkedPikaOrGrassPlatformSprites(u8 taskId, u8 state)
{
    u8 i;

    for (i = 0; i < 3; i++)
    {
        DestroySprite(&gSprites[gTasks[taskId].data[7 + i]]);
    }

    switch (state)
    {
    case LOAD_PIKA:
        FreeSpriteTilesByTag(TAG_PIKA_EYES);
        FreeSpriteTilesByTag(TAG_PIKA_2);
        FreeSpriteTilesByTag(TAG_PIKA_1);
        FreeSpritePaletteByTag(TAG_PIKA_1);
        break;
    case LOAD_PLATFORM:
        FreeSpriteTilesByTag(TAG_GRASS_PLATFORM);
        FreeSpritePaletteByTag(TAG_GRASS_PLATFORM);
        break;
    }
}

static void LoadOaksSpeechTrainerPic(u16 whichPic, u16 tileOffset)
{
    u32 i;

    switch (whichPic)
    {
    case 0: // FIRE
        LoadPalette(sOakSpeechGfx_RedPal, 0x40, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_RedPic, (void *)0x06000600 + tileOffset);
        break;
    case 1: // LEAF
        LoadPalette(sOakSpeechGfx_LeafPal, 0x40, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_LeafPic, (void *)0x06000600 + tileOffset);
        break;
    case 2: // BLUE
        LoadPalette(sOakSpeechGfx_RivalPal, 0x60, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_RivalPic, (void *)0x06000600 + tileOffset);
        break;
    case 3: // OAK
        LoadPalette(sOakSpeechGfx_OakPal, 0x60, 0x40);
        LZ77UnCompVram(sOakSpeechGfx_OakPic, (void *)0x06000600 + tileOffset);
        break;
    default:
        return;
    }

    sOakSpeechResources->trainerPicTilemapBuffer = AllocZeroed(0x60);
    for (i = 0; i < 0x60; i++)
        ((u8 *)sOakSpeechResources->trainerPicTilemapBuffer)[i] = i;
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 32, 32, 0x10);
    CopyRectToBgTilemapBufferRect(2, sOakSpeechResources->trainerPicTilemapBuffer, 0, 0, 8, 12, 11, 2, 8, 12, 0x10, (tileOffset / 64) + 0x18, 0x00);
    CopyBgTilemapBufferToVram(2);
    Free(sOakSpeechResources->trainerPicTilemapBuffer);
    sOakSpeechResources->trainerPicTilemapBuffer = 0;
}

static void DestroyOaksSpeechTrainerPic(void)
{
    FillBgTilemapBufferRect(2, 0x000, 11, 1, 8, 12, 0x10);
    CopyBgTilemapBufferToVram(2);
}

static void Task_SlowFadeIn(u8 taskId)
{
    u8 i = 0;
    if (gTasks[taskId].data[1] == 0)
    {
        gTasks[gTasks[taskId].data[0]].data[2] = 1;
        DestroyTask(taskId);
        for (i = 0; i < 3; i++)
        {
            gSprites[gTasks[taskId].data[7 + i]].invisible = TRUE;
        }
    }
    else
    {
        if (gTasks[taskId].data[4] != 0)
            gTasks[taskId].data[4]--;
        else
        {
            gTasks[taskId].data[4] = gTasks[taskId].data[3];
            gTasks[taskId].data[1]--;
            gTasks[taskId].data[2]++;
            if (gTasks[taskId].data[1] == 8)
            {
                for (i = 0; i < 3; i++)
                {
                    gSprites[gTasks[taskId].data[7 + i]].invisible ^= TRUE;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (gTasks[taskId].data[2] * 256) + gTasks[taskId].data[1]);
        }
    }
}

static void CreateFadeInTask(u8 taskId, u8 state)
{
    u8 taskId2;
    u8 i = 0;

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0x10);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    gTasks[taskId].data[2] = 0;
    taskId2 = CreateTask(Task_SlowFadeIn, 0);
    gTasks[taskId2].data[0] = taskId;
    gTasks[taskId2].data[1] = 16;
    gTasks[taskId2].data[2] = 0;
    gTasks[taskId2].data[3] = state;
    gTasks[taskId2].data[4] = state;
    for (i = 0; i < 3; i++)
    {
        gTasks[taskId2].data[7 + i] = gTasks[taskId].data[7 + i];
    }
}

static void Task_SlowFadeOut(u8 taskId)
{
    u8 i = 0;

    if (gTasks[taskId].data[1] == 16)
    {
        if (!gPaletteFade.active)
        {
            gTasks[gTasks[taskId].data[0]].data[2] = 1;
            DestroyTask(taskId);
        }
    }
    else
    {
        if (gTasks[taskId].data[4] != 0)
            gTasks[taskId].data[4]--;
        else
        {
            gTasks[taskId].data[4] = gTasks[taskId].data[3];
            gTasks[taskId].data[1] += 2;
            gTasks[taskId].data[2] -= 2;
            if (gTasks[taskId].data[1] == 8)
            {
                for (i = 0; i < 3; i++)
                {
                    gSprites[gTasks[taskId].data[7 + i]].invisible ^= TRUE;
                }
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, (gTasks[taskId].data[2] * 256) + gTasks[taskId].data[1]);
        }
    }
}

static void CreateFadeOutTask(u8 taskId, u8 state)
{
    u8 taskId2;
    u8 i = 0;

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_OBJ);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    SetGpuReg(REG_OFFSET_BLDY, 0);
    gTasks[taskId].data[2] = 0;
    taskId2 = CreateTask(Task_SlowFadeOut, 0);
    gTasks[taskId2].data[0] = taskId;
    gTasks[taskId2].data[1] = 0;
    gTasks[taskId2].data[2] = 16;
    gTasks[taskId2].data[3] = state;
    gTasks[taskId2].data[4] = state;
    for (i = 0; i < 3; i++)
    {
        gTasks[taskId2].data[7 + i] = gTasks[taskId].data[7 + i];
    }
}

static void PrintNameChoiceOptions(u8 taskId, u8 state)
{
    s16 * data = gTasks[taskId].data;
    const u8 *const * textPtrs;
    u8 i;

    data[13] = AddWindow(&sNewGameAdventureIntroWindowTemplates[3]);
    PutWindowTilemap(data[13]);
    DrawStdFrameWithCustomTileAndPalette(data[13], 1, GetStdWindowBaseTileNum(), 14);
    FillWindowPixelBuffer(gTasks[taskId].data[13], PIXEL_FILL(1));
    AddTextPrinterParameterized(data[13], 2, gOtherText_NewName, 8, 1, 0, NULL);
    if (state == 0)
        textPtrs = gSaveBlock2Ptr->playerGender == MALE ? gMalePresetNames : gFemalePresetNames;
    else
        textPtrs = sRivalNameChoices;
    for (i = 0; i < 4; i++)
    {
        AddTextPrinterParameterized(data[13], 2, textPtrs[i], 8, 16 * (i + 1) + 1, 0, NULL);
    }
    Menu_InitCursor(data[13], 2, 0, 1, 16, 5, 0);
    CopyWindowToVram(data[13], COPYWIN_BOTH);
}

static void GetDefaultName(u8 playerOrRival, u8 namePick)
{
    const u8 * src;
    u8 * dest;
    u8 i;

    if (playerOrRival == 0)
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
            src = gMalePresetNames[Random() % 19];
        else
            src = gFemalePresetNames[Random() % 19];
        dest = gSaveBlock2Ptr->playerName;
    }
    else
    {
        src = sRivalNameChoices[namePick];
        dest = gSaveBlock1Ptr->rivalName;
    }
    for (i = 0; i < PLAYER_NAME_LENGTH && src[i] != EOS; i++)
        dest[i] = src[i];
    for (; i < PLAYER_NAME_LENGTH + 1; i++)
        dest[i] = EOS;
}
