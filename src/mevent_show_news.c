#include "global.h"
#include "gflib.h"
#include "menu_indicators.h"
#include "new_menu_helpers.h"
#include "mevent.h"
#include "mystery_gift_menu.h"
#include "menu.h"
#include "link_rfu.h"

#define UP    0
#define DOWN  1

struct WonderNewsWork
{
    /*0000*/ struct MEWonderNewsData wonderNews;
    /*01bc*/ const struct MysteryEventCardOrNewsGfxTemplate * bgSpec;
    /*01c0*/ u8 verticalScrollDisabled:1;
             u8 state:7;
    /*01c1*/ u8 menuIndicatorsId;
    /*01c2*/ u8 inputDisabled:1;
             u8 yScrollSpeed:7;
    /*01c3*/ u8 scrollDirection:1;
             u8 yPos:7;
    /*01c4*/ u16 fullyDownThreshold;
    /*01c6*/ u16 scrollOffset;
    /*01c8*/ u16 windowIds[2];
    /*01cc*/ u8 filler_01CC[2];
    /*01ce*/ u8 title[41];
    /*01f7*/ u8 messages[10][41];
    /*0394*/ struct ScrollArrowsTemplate scrollArrowsTemplate;
    /*03a4*/ u8 decompressBuffer[0x1000];
};

static EWRAM_DATA struct WonderNewsWork * sWork = NULL;

static void WonderNews_CopyMessageBuffersToTemp(void);
static void WonderNews_PrintTitleAndMessages(void);
static void WonderNews_ScrollList(void);

static const u8 sTextPals[][3] = {
    {0, 2, 3},
    {0, 1, 2}
};
static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 0,
        .width = 28,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x000
    },
    {
        .bg = 2,
        .tilemapLeft = 1,
        .tilemapTop = 3,
        .width = 28,
        .height = 20,
        .paletteNum = 15,
        .baseBlock = 0x000
    }
};
static const struct ScrollArrowsTemplate sScrollArrowsTemplate = {
    0x02, 0xe8, 0x18, 0x03, 0xe8, 0x98,
    0x0000, 0x0002, 0x1000, 0x1000, 0x0,
};

static const u16 sNews1Pal[] = INCBIN_U16("graphics/mevent/pal_468060.gbapal");
static const u16 sNews6Pal[] = INCBIN_U16("graphics/mevent/pal_468080.gbapal");
static const u16 sNews7Pal[] = INCBIN_U16("graphics/mevent/pal_4680A0.gbapal");
static const u8 sNews0Gfx[] = INCBIN_U8("graphics/mevent/gfx_4680C0.4bpp.lz");
static const u8 sNews0Map[] = INCBIN_U8("graphics/mevent/tilemap_468140.bin.lz");
static const u8 sNews1Gfx[] = INCBIN_U8("graphics/mevent/gfx_46821C.4bpp.lz");
static const u8 sNews1Map[] = INCBIN_U8("graphics/mevent/tilemap_46824C.bin.lz");
static const u8 sNews2Gfx[] = INCBIN_U8("graphics/mevent/gfx_46830C.4bpp.lz");
static const u8 sNews2Map[] = INCBIN_U8("graphics/mevent/tilemap_46837C.bin.lz");
static const u8 sNews6Gfx[] = INCBIN_U8("graphics/mevent/gfx_468448.4bpp.lz");
static const u8 sNews6Map[] = INCBIN_U8("graphics/mevent/tilemap_4684D8.bin.lz");
static const u8 sNews7Gfx[] = INCBIN_U8("graphics/mevent/gfx_468448.4bpp.lz");    // Duplicate
static const u8 sNews7Map[] = INCBIN_U8("graphics/mevent/tilemap_4684D8.bin.lz"); // Duplicate

static const struct MysteryEventCardOrNewsGfxTemplate sBgSpecs[] = {
    {1, 0, 0, 0, sNews0Gfx, sNews0Map, sNews1Pal},
    {1, 0, 0, 0, sNews1Gfx, sNews1Map, gCard1Pal},
    {1, 0, 0, 0, sNews2Gfx, sNews2Map, gCard2Pal},
    {1, 0, 0, 0, sNews2Gfx, sNews2Map, gCard3Pal},
    {1, 0, 0, 0, sNews2Gfx, sNews2Map, gCard4Pal},
    {1, 0, 0, 0, sNews2Gfx, sNews2Map, gCard5Pal},
    {1, 0, 0, 0, sNews6Gfx, sNews6Map, sNews6Pal},
    {1, 0, 0, 0, sNews7Gfx, sNews7Map, sNews7Pal}
};

bool32 InitWonderNewsResources(const struct MEWonderNewsData * news)
{
    if (news == NULL)
        return FALSE;
    sWork = AllocZeroed(sizeof(struct WonderNewsWork));
    if (sWork == NULL)
        return FALSE;
    sWork->wonderNews = *news;
    if (sWork->wonderNews.unk_03 >= NELEMS(sBgSpecs))
        sWork->wonderNews.unk_03 = 0;
    sWork->bgSpec = &sBgSpecs[sWork->wonderNews.unk_03];
    sWork->menuIndicatorsId = 0xFF;
    return TRUE;
}

void DestroyWonderNewsResources(void)
{
    if (sWork != NULL)
    {
        *sWork = (struct WonderNewsWork){};
        Free(sWork);
        sWork = NULL;
    }
}

s32 FadeToWonderNewsMenu(void)
{
    if (sWork == NULL)
        return -1;

    switch (sWork->state)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        break;
    case 1:
        if (UpdatePaletteFade())
            return 0;
        ChangeBgY(0, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgY(2, 0, 0);
        ChangeBgY(3, 0, 0);
        SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0, 240));
        SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(26, 152));
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ);
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
        break;
    case 2:
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(3, 0x000, 0, 0, 30, 20);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        DecompressAndCopyTileDataToVram(3, sWork->bgSpec->tiles, 0, 8, 0);
        sWork->windowIds[0] = AddWindow(&sWindowTemplates[0]);
        sWork->windowIds[1] = AddWindow(&sWindowTemplates[1]);
        break;
    case 3:
        if (FreeTempTileDataBuffersIfPossible())
            return 0;
        gPaletteFade.bufferTransferDisabled = TRUE;
        LoadPalette(sWork->bgSpec->pal, 0x10, 0x20);
        LZ77UnCompWram(sWork->bgSpec->map, sWork->decompressBuffer);
        CopyRectToBgTilemapBufferRect(1, sWork->decompressBuffer, 0, 0, 30, 3, 0, 0, 30, 3, 1, 8, 0);
        CopyRectToBgTilemapBufferRect(3, sWork->decompressBuffer, 0, 3, 30, 23, 0, 3, 30, 23, 1, 8, 0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(3);
        break;
    case 4:
        WonderNews_CopyMessageBuffersToTemp();
        break;
    case 5:
        WonderNews_PrintTitleAndMessages();
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(2);
        break;
    case 6:
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        gPaletteFade.bufferTransferDisabled = FALSE;
        sWork->menuIndicatorsId = AddScrollIndicatorArrowPair(&sWork->scrollArrowsTemplate, &sWork->scrollOffset);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        UpdatePaletteFade();
        break;
    default:
        if (UpdatePaletteFade())
            return 0;
        sWork->state = 0;
        return 1;
    }

    ++sWork->state;
    return 0;
}

s32 FadeOutFromWonderNews(bool32 flag)
{
    if (sWork == NULL)
        return -1;
    switch (sWork->state)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        break;
    case 1:
        if (UpdatePaletteFade())
            return 0;
        ChangeBgY(2, 0, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON);
        break;
    case 2:
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 30, 24);
        FillBgTilemapBufferRect_Palette0(3, 0x000, 0, 0, 30, 24);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        break;
    case 3:
        HideBg(1);
        HideBg(2);
        RemoveWindow(sWork->windowIds[1]);
        RemoveWindow(sWork->windowIds[0]);
        break;
    case 4:
        ChangeBgY(2, 0, 0);
        ChangeBgY(3, 0, 0);
        if (sWork->menuIndicatorsId != 0xFF)
        {
            RemoveScrollIndicatorArrowPair(sWork->menuIndicatorsId);
            sWork->menuIndicatorsId = 0xFF;
        }
        break;
    case 5:
        PrintMysteryGiftOrEReaderTopMenu(gGiftIsFromEReader, flag);
        break;
    case 6:
        MG_DrawCheckerboardPattern();
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(3);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        break;
    default:
        if (UpdatePaletteFade())
            return 0;
        sWork->state = 0;
        return 1;
    }
    ++sWork->state;
    return 0;
}

void MENews_RemoveScrollIndicatorArrowPair(void)
{
    if (!sWork->verticalScrollDisabled && sWork->menuIndicatorsId != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(sWork->menuIndicatorsId);
        sWork->menuIndicatorsId = 0xFF;
        sWork->verticalScrollDisabled = TRUE;
    }
}


void MENews_AddScrollIndicatorArrowPair(void)
{
    if (sWork->verticalScrollDisabled)
    {
        sWork->menuIndicatorsId = AddScrollIndicatorArrowPair(&sWork->scrollArrowsTemplate, &sWork->scrollOffset);
        sWork->verticalScrollDisabled = FALSE;
    }
}

u32 MENews_GetInput(u16 input)
{
    if (sWork->inputDisabled)
    {
        WonderNews_ScrollList();
        return 0xFF;
    }
    switch (input)
    {
    case A_BUTTON:
        return 0;
    case B_BUTTON:
        return 1;
    case DPAD_UP:
        if (sWork->scrollOffset == 0)
            return 0xFF;
        if (sWork->verticalScrollDisabled)
            return 0xFF;
        sWork->scrollDirection = UP;
        break;
    case DPAD_DOWN:
        if (sWork->scrollOffset == sWork->fullyDownThreshold)
            return 0xFF;
        if (sWork->verticalScrollDisabled)
            return 0xFF;
        sWork->scrollDirection = DOWN;
        break;
    default:
        return 0xFF;
    }
    sWork->inputDisabled = TRUE;
    sWork->yScrollSpeed = 2;
    sWork->yPos = 0;
    if (sWork->scrollDirection == UP)
        return 2;
    else
        return 3;
}

static void WonderNews_CopyMessageBuffersToTemp(void)
{
    u8 i = 0;
    memcpy(sWork->title, sWork->wonderNews.title, 40);
    sWork->title[40] = EOS;
    for (; i < 10; ++i)
    {
        memcpy(sWork->messages[i], sWork->wonderNews.messages[i], 40);
        sWork->messages[i][40] = EOS;
        if (i > 7 && sWork->messages[i][0] != EOS)
            ++sWork->fullyDownThreshold;
    }
    sWork->scrollArrowsTemplate = sScrollArrowsTemplate;
    sWork->scrollArrowsTemplate.fullyDownThreshold = sWork->fullyDownThreshold;
}

static void WonderNews_PrintTitleAndMessages(void)
{
    u8 i = 0;
    s32 x;
    PutWindowTilemap(sWork->windowIds[0]);
    PutWindowTilemap(sWork->windowIds[1]);
    FillWindowPixelBuffer(sWork->windowIds[0], 0);
    FillWindowPixelBuffer(sWork->windowIds[1], 0);
    x = ((28 * 8) - GetStringWidth(3, sWork->title, GetFontAttribute(3, 2))) / 2; // center align
    // don't escape left bound
    if (x < 0)
        x = 0;
    AddTextPrinterParameterized3(sWork->windowIds[0], 3, x, 6, sTextPals[sWork->bgSpec->textPal1], 0, sWork->title);
    for (; i < 10; ++i)
    {
        AddTextPrinterParameterized3(sWork->windowIds[1], 3, 0, 16 * i + 2, sTextPals[sWork->bgSpec->textPal2], 0, sWork->messages[i]);
    }
    CopyWindowToVram(sWork->windowIds[0], COPYWIN_BOTH);
    CopyWindowToVram(sWork->windowIds[1], COPYWIN_BOTH);
}

static void WonderNews_ScrollList(void)
{
    fx16 r4 = Q_8_8(sWork->yScrollSpeed);
    if (sWork->scrollDirection != UP)
    {
        ChangeBgY(2, r4, BG_SCROLL_ADD);
        ChangeBgY(3, r4, BG_SCROLL_ADD);
    }
    else
    {
        ChangeBgY(2, r4, BG_SCROLL_SUB);
        ChangeBgY(3, r4, BG_SCROLL_SUB);
    }
    sWork->yPos += sWork->yScrollSpeed;
    if (sWork->yPos > 15)
    {
        if (sWork->scrollDirection != UP)
            ++sWork->scrollOffset;
        else
            --sWork->scrollOffset;
        sWork->inputDisabled = FALSE;
        sWork->yPos = 0;
    }
}
