#ifndef GUARD_BAG_H
#define GUARD_BAG_H

#include "menu_helpers.h"

enum {
    BAGWIN_QUANTITY,
    BAGWIN_1,
    BAGWIN_MONEY,
    BAGWIN_YESNO_BOTTOM,
    BAGWIN_YESNO_TOP,
    BAGWIN_MESSAGE_BOX,
    BAGWIN_TOSS_DEPOSIT_MSG,
    BAGWIN_7,
    BAGWIN_8,
    BAGWIN_9,
    BAGWIN_CONTEXT_MENU,
    BAGWIN_11,
    BAGWIN_12,
    BAGWIN_13,
};

void InitBagWindows(void);
void BagPrintTextOnWindow(u8 windowId, u8 fontId, const u8 * str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx);
void BagPrintTextOnWin1CenteredColor0(const u8 * str, u8 unused);
void BagDrawDepositItemTextBox(void);
u8 ShowBagWindow(u8 whichWindow, u8 nItems);
void HideBagWindow(u8 whichWindow);
u8 OpenBagWindow(u8 whichWindow);
void CloseBagWindow(u8 whichWindow);
u8 GetBagWindow(u8 whichWindow);
void BagCreateYesNoMenuBottomRight(u8 taskId, const struct YesNoFuncTable * ptrs);
void BagCreateYesNoMenuTopRight(u8 taskId, const struct YesNoFuncTable * ptrs);
void BagPrintMoneyAmount(void);
void BagDrawTextBoxOnWindow(u8 windowId);

#endif //GUARD_BAG_H
