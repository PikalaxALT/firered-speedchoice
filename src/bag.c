#include "global.h"
#include "gflib.h"
#include "item_menu.h"
#include "text_window.h"
#include "menu_helpers.h"
#include "new_menu_helpers.h"
#include "menu.h"
#include "money.h"
#include "bag.h"
#include "strings.h"

static const u16 sBagWindowPalF[] = INCBIN_U16("graphics/item_menu/bag_window_pal.gbapal");

static const u8 sTextColors[][3] = {
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GREY},
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GREY, TEXT_COLOR_LIGHT_GREY},
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_GREY, TEXT_COLOR_DARK_GREY},
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE, TEXT_COLOR_LIGHT_BLUE}
};

static const struct WindowTemplate sDefaultBagWindowsStd[] = {
    [BAGWIN_STD_ITEMS_LIST] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 1,
        .width = 18,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0x08a
    },
    [BAGWIN_STD_ITEM_DESC] = {
        .bg = 0,
        .tilemapLeft = 5,
        .tilemapTop = 14,
        .width = 25,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x162
    },
    [BAGWIN_STD_POCKET_NAME] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 9,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x1f8
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sDefaultBagWindowsDeposit[] = {
    [BAGWIN_STD_ITEMS_LIST] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 1,
        .width = 18,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 0x08a
    },
    [BAGWIN_STD_ITEM_DESC] = {
        .bg = 0,
        .tilemapLeft = 5,
        .tilemapTop = 14,
        .width = 25,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x162
    },
    [BAGWIN_STD_POCKET_NAME] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 12,
        .baseBlock = 0x1f8
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sWindowTemplates[] = {
    
    [BAGWIN_QUANTITY + 0] = {
        .bg = 0,
        .tilemapLeft = 24,
        .tilemapTop = 15,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x242
    }, 
    [BAGWIN_QUANTITY + 1] = {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 9,
        .width = 12,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x242
    }, 
    [BAGWIN_MONEY] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 8,
        .height = 3,
        .paletteNum = 12,
        .baseBlock = 0x272
    }, 
    [BAGWIN_YESNO_BOTTOM] = {
        .bg = 0,
        .tilemapLeft = 23,
        .tilemapTop = 15,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x28a
    }, 
    [BAGWIN_YESNO_TOP] = {
        .bg = 0,
        .tilemapLeft = 21,
        .tilemapTop = 9,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x28a
    }, 
    [BAGWIN_MESSAGE_BOX] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x2a2
    }, 
    [BAGWIN_TOSS_DEPOSIT_MSG + 0] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 14,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x2a2
    }, 
    [BAGWIN_TOSS_DEPOSIT_MSG + 1] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 15,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x2da
    }, 
    [BAGWIN_TOSS_DEPOSIT_MSG + 2] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 16,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x316
    }, 
    [BAGWIN_TOSS_DEPOSIT_MSG + 3] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 15,
        .width = 23,
        .height = 4,
        .paletteNum = 12,
        .baseBlock = 0x356
    }, 
    [BAGWIN_CONTEXT_MENU + 0] = {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 17,
        .width = 7,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, 
    [BAGWIN_CONTEXT_MENU + 1] = {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 15,
        .width = 7,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, 
    [BAGWIN_CONTEXT_MENU + 2] = {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 13,
        .width = 7,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }, 
    [BAGWIN_CONTEXT_MENU + 3] = {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 11,
        .width = 7,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 0x20a
    }
};

static const u8 sUnusedTextScrollTime[] = {
    [OPTIONS_TEXT_SPEED_SLOW] = 16,
    [OPTIONS_TEXT_SPEED_MID]  =  8,
    [OPTIONS_TEXT_SPEED_FAST] =  4,
    [OPTIONS_TEXT_SPEED_INST] =  1,
};

static EWRAM_DATA u8 sOpenWindows[BAGWIN_UNIQUE_COUNT] = {};

void InitBagWindows(void)
{
    u8 i;

    if (gBagMenuState.location != ITEMMENULOCATION_ITEMPC)
        InitWindows(sDefaultBagWindowsStd);
    else
        InitWindows(sDefaultBagWindowsDeposit);
    DeactivateAllTextPrinters();
    TextWindow_SetUserSelectedFrame(BAGWIN_STD_ITEMS_LIST, 0x64, 0xE0);
    TextWindow_LoadResourcesStdFrame0(BAGWIN_STD_ITEMS_LIST, 0x6D, 0xD0);
    TextWindow_SetStdFrame0_WithPal(BAGWIN_STD_ITEMS_LIST, 0x81, 0xC0);
    LoadPalette(sBagWindowPalF, 0xF0, 0x20);
    for (i = 0; i < BAGWIN_STD_COUNT; i++)
    {
        FillWindowPixelBuffer(i, 0x00);
        PutWindowTilemap(i);
    }
    ScheduleBgCopyTilemapToVram(0);
    for (i = 0; i < BAGWIN_UNIQUE_COUNT; i++)
    {
        sOpenWindows[i] = 0xFF;
    }
}

void BagPrintTextOnWindow(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx)
{
    AddTextPrinterParameterized4(windowId, fontId, x, y, letterSpacing, lineSpacing, sTextColors[colorIdx], speed, str);
}

void BagPrintTextOnWin1CenteredColor0(const u8 * str, u8 unused)
{
    u32 x = 0x48 - GetStringWidth(1, str, 0);
    AddTextPrinterParameterized3(BAGWIN_STD_POCKET_NAME, 1, x / 2, 1, sTextColors[0], 0, str);
}

void BagDrawDepositItemTextBox(void)
{
    u32 x;
    DrawStdFrameWithCustomTileAndPalette(BAGWIN_STD_POCKET_NAME, FALSE, 0x081, 0x0C);
    x = 0x40 - GetStringWidth(0, gText_DepositItem, 0);
    AddTextPrinterParameterized(BAGWIN_STD_POCKET_NAME, 0, gText_DepositItem, x / 2, 1, 0, NULL);
}

u8 ShowBagWindow(u8 whichWindow, u8 nItems)
{
    if (sOpenWindows[whichWindow] == 0xFF)
    {
        sOpenWindows[whichWindow] = AddWindow(&sWindowTemplates[whichWindow + nItems]);
        if (whichWindow != 6)
        {
            DrawStdFrameWithCustomTileAndPalette(sOpenWindows[whichWindow], FALSE, 0x064, 0xE);
        }
        else
        {
            DrawStdFrameWithCustomTileAndPalette(sOpenWindows[whichWindow], FALSE, 0x081, 0xC);
        }
        ScheduleBgCopyTilemapToVram(0);
    }
    return sOpenWindows[whichWindow];
}

void HideBagWindow(u8 whichWindow)
{
    ClearStdWindowAndFrameToTransparent(sOpenWindows[whichWindow], FALSE);
    ClearWindowTilemap(sOpenWindows[whichWindow]);
    RemoveWindow(sOpenWindows[whichWindow]);
    ScheduleBgCopyTilemapToVram(0);
    sOpenWindows[whichWindow] = 0xFF;
}

u8 OpenBagWindow(u8 whichWindow)
{
    if (sOpenWindows[whichWindow] == 0xFF)
    {
        sOpenWindows[whichWindow] = AddWindow(&sWindowTemplates[whichWindow]);
    }
    return sOpenWindows[whichWindow];
}

void CloseBagWindow(u8 whichWindow)
{
    if (sOpenWindows[whichWindow] != 0xFF)
    {
        ClearDialogWindowAndFrameToTransparent(sOpenWindows[whichWindow], FALSE);
        ClearWindowTilemap(sOpenWindows[whichWindow]);
        RemoveWindow(sOpenWindows[whichWindow]);
        PutWindowTilemap(BAGWIN_STD_ITEM_DESC);
        ScheduleBgCopyTilemapToVram(0);
        sOpenWindows[whichWindow] = 0xFF;
    }
}

u8 GetBagWindow(u8 whichWindow)
{
    return sOpenWindows[whichWindow];
}

void BagCreateYesNoMenuBottomRight(u8 taskId, const struct YesNoFuncTable * ptrs)
{
    CreateYesNoMenuWithCallbacks(taskId, &sWindowTemplates[BAGWIN_YESNO_BOTTOM], 2, 0, 2, 0x064, 0x0E, ptrs);
}

void BagCreateYesNoMenuTopRight(u8 taskId, const struct YesNoFuncTable * ptrs)
{
    CreateYesNoMenuWithCallbacks(taskId, &sWindowTemplates[BAGWIN_YESNO_TOP], 2, 0, 2, 0x064, 0x0E, ptrs);
}

void BagPrintMoneyAmount(void)
{
    PrintMoneyAmountInMoneyBoxWithBorder(ShowBagWindow(BAGWIN_MONEY, 0), 0x081, 0x0C, GetMoney(&gSaveBlock1Ptr->money));
}

void BagDrawTextBoxOnWindow(u8 windowId)
{
    DrawTextBorderOuter(windowId, 0x064, 0x0E);
}
