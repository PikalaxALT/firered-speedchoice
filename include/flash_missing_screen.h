#ifndef POKEFIRERED_FLASH_MISSING_SCREEN_H
#define POKEFIRERED_FLASH_MISSING_SCREEN_H

enum {
    FATAL_NO_FLASH = 0,
    FATAL_ACCU_FAIL
};

void CB2_FlashMissingScreen(void);
extern u8 gWhichErrorMessage;

#endif //POKEFIRERED_FLASH_MISSING_SCREEN_H
