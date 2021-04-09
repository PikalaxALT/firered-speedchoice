#include "global.h"
#include "gflib.h"
#include "task.h"
#include "text_window_graphics.h"
#include "scanline_effect.h"
#include "nes_pipeline_fail_screen.h"
#include "text_window.h"
#include "new_menu_helpers.h"
#include "constants/songs.h"

EWRAM_DATA static u8 gEmulatorCheck = 0;

NAKED
static void NESPipelineTest_Internal(void)
{
    // Copied from NES emulator pipeline checks.
    asm(
        ".arm\n"
        "mov r2, lr\n"
        // Ensure the pipeline test is not disturbed. It seems strange but whatever.
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "mov r1, #0\n"
        "add lr, pc, #8\n"
        "ldr r0, [pc, #-16]\n" // mov r1, #0
        "str r0, [lr, #0]\n"
        "mov r1, #255\n"
        "mov r1, #255\n" // This gets overwritten
        "ldr r0, =gEmulatorCheck\n"
        "strb r1, [r0]\n"
        "bx r2\n"
        ".pool"
        );
}

u8 NESPipelineTest(void)
{
    static u8 buffer[0x4C];
    memcpy(buffer, (const void *)((uintptr_t)NESPipelineTest_Internal & ~3), 0x4C);
    ((void (*)(void))buffer)();
    return gEmulatorCheck;
}
