#include "global.h"
#include "text_window_graphics.h"

const u16 gSignPostWindowTiles[] = INCBIN_U16("graphics/text_window/signpost_tiles.4bpp");

static const u16 sWindowFrameTiles_1[] = INCBIN_U16("graphics/text_window/player_frame_1.4bpp");
static const u16 sWindowFrameTiles_2[] = INCBIN_U16("graphics/text_window/player_frame_2.4bpp");
static const u16 gUnk_Empty_Space_8470FAC[16] = {0};
static const u16 sWindowFrameTiles_3[] = INCBIN_U16("graphics/text_window/player_frame_3.4bpp");
static const u16 sWindowFrameTiles_4[] = INCBIN_U16("graphics/text_window/player_frame_4.4bpp");
static const u16 sWindowFrameTiles_5[] = INCBIN_U16("graphics/text_window/player_frame_5.4bpp");
static const u16 sWindowFrameTiles_6[] = INCBIN_U16("graphics/text_window/player_frame_6.4bpp");
static const u16 sWindowFrameTiles_7[] = INCBIN_U16("graphics/text_window/player_frame_7.4bpp");
static const u16 sWindowFrameTiles_8[] = INCBIN_U16("graphics/text_window/player_frame_8.4bpp");
static const u16 gUnk_Empty_Space_847168C[16] = {0};
static const u16 sWindowFrameTiles_9[] = INCBIN_U16("graphics/text_window/player_frame_9.4bpp");
static const u16 sWindowFrameTiles_10[] = INCBIN_U16("graphics/text_window/player_frame_10.4bpp");
static const u16 gUnk_Empty_Space_84718EC[16] = {0};
static const u16 sWindowFramePals_1[] = INCBIN_U16("graphics/text_window/player_frame_1.gbapal");
static const u16 sWindowFramePals_2[] = INCBIN_U16("graphics/text_window/player_frame_2.gbapal");
static const u16 sWindowFramePals_3[] = INCBIN_U16("graphics/text_window/player_frame_3.gbapal");
static const u16 sWindowFramePals_4[] = INCBIN_U16("graphics/text_window/player_frame_4.gbapal");
static const u16 sWindowFramePals_5[] = INCBIN_U16("graphics/text_window/player_frame_5.gbapal");
static const u16 sWindowFramePals_6[] = INCBIN_U16("graphics/text_window/player_frame_6.gbapal");
static const u16 sWindowFramePals_7[] = INCBIN_U16("graphics/text_window/player_frame_7.gbapal");
static const u16 sWindowFramePals_8[] = INCBIN_U16("graphics/text_window/player_frame_8.gbapal");
static const u16 sWindowFramePals_9[] = INCBIN_U16("graphics/text_window/player_frame_9.gbapal");
static const u16 sWindowFramePals_10[] = INCBIN_U16("graphics/text_window/player_frame_10.gbapal");

const u16 gStdFrame0[] = INCBIN_U16("graphics/text_window/std_frame_0.4bpp");
const u16 gStdFrame1[] = INCBIN_U16("graphics/text_window/std_frame_1.4bpp");

const u16 gStdPals[][16] = {
    INCBIN_U16("graphics/text_window/stdpal_0.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_1.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_2.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_3.gbapal"),
    INCBIN_U16("graphics/text_window/stdpal_4.gbapal")
};

const struct TextWindowGraphics gUserFrames[] = {
    {sWindowFrameTiles_1, sWindowFramePals_1},
    {sWindowFrameTiles_2, sWindowFramePals_2},
    {sWindowFrameTiles_3, sWindowFramePals_3},
    {sWindowFrameTiles_4, sWindowFramePals_4},
    {sWindowFrameTiles_5, sWindowFramePals_5},
    {sWindowFrameTiles_6, sWindowFramePals_6},
    {sWindowFrameTiles_7, sWindowFramePals_7},
    {sWindowFrameTiles_8, sWindowFramePals_8},
    {sWindowFrameTiles_9, sWindowFramePals_9},
    {sWindowFrameTiles_10, sWindowFramePals_10}
}; // NELEMS = 10

const struct TextWindowGraphics * GetUserFrameGraphicsInfo(u8 idx)
{
    if (idx >= 20) // if (idx >= NELEMS(gUserFrames))
        return &gUserFrames[0];
    else
        return &gUserFrames[idx];
}
