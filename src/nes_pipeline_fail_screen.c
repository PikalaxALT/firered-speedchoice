#include "global.h"
#include "nes_pipeline_fail_screen.h"

EWRAM_DATA u32 gEmulatorCheck = 0;
static u8 buffer[512];

extern const char NESPipelineTest_Internal[];
extern const char NESPipelineTest_Internal_End[];

bool8 DoTest(const char * start, const char * end, u32 expectedValue, u8 evalWidth)
{
    memcpy(buffer, start, end - start);
    ((void (*)(void))buffer)();
    switch (evalWidth)
    {
    case TEST_EXPECT_8:
        return (u8)gEmulatorCheck == (u8)expectedValue;
    case TEST_EXPECT_16:
        return (u16)gEmulatorCheck == (u16)expectedValue;
    case TEST_EXPECT_32:
    default:
        return (u32)gEmulatorCheck == (u32)expectedValue;
    }
}

bool8 NESPipelineTest(void)
{
    return DoTest(
        NESPipelineTest_Internal,
        NESPipelineTest_Internal_End,
        255,
        TEST_EXPECT_8
    );
}
