#ifndef POKEFIRERED_FLASH_MISSING_SCREEN_H
#define POKEFIRERED_FLASH_MISSING_SCREEN_H

enum {
    FATAL_NO_FLASH = 0,
    FATAL_ACCU_FAIL,
    FATAL_OKAY = 255,
};

void CB2_FlashMissingScreen(void);
extern u8 gWhichErrorMessage;
extern u8 gWhichTestFailed[];

#endif //POKEFIRERED_FLASH_MISSING_SCREEN_H
