#include "global.h"
#include "gflib.h"
#include "decompress.h"
#include "task.h"
#include "wild_pokemon_area.h"
#include "pokedex_area_markers.h"

static const u16 sMarkerPal[] = INCBIN_U16("graphics/pokedex_area_markers/marker.gbapal");
static const u32 sMarkerTiles[] = INCBIN_U32("graphics/pokedex_area_markers/marker.4bpp.lz");

enum
{
    AREAMARKER_SQUARE,
    AREAMARKER_H_RECT_SM,
    AREAMARKER_V_RECT_SM,
    AREAMARKER_H_RECT_MD,
    AREAMARKER_V_RECT_MD,
    AREAMARKER_H_RECT_LG,
    AREAMARKER_V_RECT_LG,
};

static const struct Subsprite sSubsprite0 = {
    .size = ST_OAM_SIZE_0,
    .shape = ST_OAM_SQUARE,
    .priority = 1,
    .tileOffset = 0
};

static const struct Subsprite sSubsprite1 = {
    .size = ST_OAM_SIZE_0,
    .shape = ST_OAM_H_RECTANGLE,
    .priority = 1,
    .tileOffset = 1
};

static const struct Subsprite sSubsprite2 = {
    .size = ST_OAM_SIZE_0,
    .shape = ST_OAM_V_RECTANGLE,
    .priority = 1,
    .tileOffset = 3
};

static const struct Subsprite sSubsprite3 = {
    .size = ST_OAM_SIZE_2,
    .shape = ST_OAM_H_RECTANGLE,
    .priority = 1,
    .tileOffset = 5
};

static const struct Subsprite sSubsprite4 = {
    .size = ST_OAM_SIZE_2,
    .shape = ST_OAM_V_RECTANGLE,
    .priority = 1,
    .tileOffset = 13
};

static const struct Subsprite sSubsprite5 = {
    .size = ST_OAM_SIZE_2,
    .shape = ST_OAM_H_RECTANGLE,
    .priority = 1,
    .tileOffset = 21
};

static const struct Subsprite sSubsprite6 = {
    .size = ST_OAM_SIZE_2,
    .shape = ST_OAM_V_RECTANGLE,
    .priority = 1,
    .tileOffset = 29
};

static const struct Subsprite *const sSubsprites[] = {
    [AREAMARKER_SQUARE]    = &sSubsprite0,
    [AREAMARKER_H_RECT_SM] = &sSubsprite1,
    [AREAMARKER_V_RECT_SM] = &sSubsprite2,
    [AREAMARKER_H_RECT_MD] = &sSubsprite3,
    [AREAMARKER_V_RECT_MD] = &sSubsprite4,
    [AREAMARKER_H_RECT_LG] = &sSubsprite5,
    [AREAMARKER_V_RECT_LG] = &sSubsprite6
};

static const s8 sSubspriteLookupTable[][4] = {
    //                                   shape,                  x,   y
    [DEXMARKERAREA_PALLET_TOWN]      = { AREAMARKER_SQUARE,     54,  44 },
    [DEXMARKERAREA_VIRIDIAN_CITY]    = { AREAMARKER_SQUARE,     54,  28 },
    [DEXMARKERAREA_PEWTER_CITY]      = { AREAMARKER_SQUARE,     54,  12 },
    [DEXMARKERAREA_CERULEAN_CITY]    = { AREAMARKER_SQUARE,     92,  12 },
    [DEXMARKERAREA_LAVENDER_TOWN]    = { AREAMARKER_SQUARE,    110,  24 },
    [DEXMARKERAREA_VERMILION_CITY]   = { AREAMARKER_SQUARE,     92,  36 },
    [DEXMARKERAREA_CELADON_CITY]     = { AREAMARKER_SQUARE,     76,  24 },
    [DEXMARKERAREA_FUCHSIA_CITY]     = { AREAMARKER_SQUARE,     78,  52 },
    [DEXMARKERAREA_CINNABAR_ISLAND]  = { AREAMARKER_SQUARE,     54,  62 },
    [DEXMARKERAREA_INDIGO_PLATEAU]   = { AREAMARKER_SQUARE,     42,   2 },
    [DEXMARKERAREA_SAFFRON_CITY]     = { AREAMARKER_SQUARE,     92,  24 },
    [DEXMARKERAREA_ROUTE_1]          = { AREAMARKER_V_RECT_SM,  54,  32 },
    [DEXMARKERAREA_ROUTE_2]          = { AREAMARKER_V_RECT_SM,  54,  16 },
    [DEXMARKERAREA_ROUTE_3]          = { AREAMARKER_H_RECT_SM,  61,  12 },
    [DEXMARKERAREA_ROUTE_4]          = { AREAMARKER_H_RECT_SM,  77,  12 },
    [DEXMARKERAREA_ROUTE_5]          = { AREAMARKER_SQUARE,     92,  18 },
    [DEXMARKERAREA_ROUTE_6]          = { AREAMARKER_SQUARE,     92,  30 },
    [DEXMARKERAREA_ROUTE_7]          = { AREAMARKER_SQUARE,     84,  24 },
    [DEXMARKERAREA_ROUTE_8]          = { AREAMARKER_H_RECT_SM,  98,  24 },
    [DEXMARKERAREA_ROUTE_9]          = { AREAMARKER_H_RECT_SM,  98,  12 },
    [DEXMARKERAREA_ROUTE_10]         = { AREAMARKER_V_RECT_SM, 110,  12 },
    [DEXMARKERAREA_ROUTE_11]         = { AREAMARKER_H_RECT_SM,  98,  36 },
    [DEXMARKERAREA_ROUTE_12]         = { AREAMARKER_V_RECT_MD, 106,  25 },
    [DEXMARKERAREA_ROUTE_13]         = { AREAMARKER_H_RECT_SM, 100,  46 },
    [DEXMARKERAREA_ROUTE_14]         = { AREAMARKER_V_RECT_SM,  94,  45 },
    [DEXMARKERAREA_ROUTE_15]         = { AREAMARKER_H_RECT_SM,  85,  52 },
    [DEXMARKERAREA_ROUTE_16]         = { AREAMARKER_SQUARE,     68,  24 },
    [DEXMARKERAREA_ROUTE_17]         = { AREAMARKER_V_RECT_MD,  62,  26 },
    [DEXMARKERAREA_ROUTE_18]         = { AREAMARKER_H_RECT_SM,  64,  52 },
    [DEXMARKERAREA_ROUTE_19]         = { AREAMARKER_SQUARE,     78,  60 },
    [DEXMARKERAREA_ROUTE_20]         = { AREAMARKER_H_RECT_MD,  55,  58 },
    [DEXMARKERAREA_ROUTE_21]         = { AREAMARKER_V_RECT_SM,  54,  50 },
    [DEXMARKERAREA_ROUTE_22]         = { AREAMARKER_H_RECT_SM,  40,  28 },
    [DEXMARKERAREA_ROUTE_23]         = { AREAMARKER_V_RECT_MD,  38,   4 },
    [DEXMARKERAREA_ROUTE_24]         = { AREAMARKER_SQUARE,     92,   4 },
    [DEXMARKERAREA_ROUTE_25]         = { AREAMARKER_H_RECT_MD,  90, 254 },
    [DEXMARKERAREA_VIRIDIAN_FOREST]  = { AREAMARKER_SQUARE,     51,  20 },
    [DEXMARKERAREA_DIGLETTS_CAVE]    = { AREAMARKER_H_RECT_SM,  61,  18 },
    [DEXMARKERAREA_MT_MOON]          = { AREAMARKER_SQUARE,     72,   8 },
    [DEXMARKERAREA_CERULEAN_CAVE]    = { AREAMARKER_SQUARE,     87,   8 },
    [DEXMARKERAREA_ROCK_TUNNEL]      = { AREAMARKER_SQUARE,    112,  14 },
    [DEXMARKERAREA_POWER_PLANT]      = { AREAMARKER_SQUARE,    113,  20 },
    [DEXMARKERAREA_POKEMON_TOWER]    = { AREAMARKER_SQUARE,    113,  25 },
    [DEXMARKERAREA_SAFARI_ZONE]      = { AREAMARKER_H_RECT_SM,  78,  44 },
    [DEXMARKERAREA_SEAFOAM_ISLANDS]  = { AREAMARKER_SQUARE,     65,  60 },
    [DEXMARKERAREA_POKEMON_MANSION]  = { AREAMARKER_SQUARE,     52,  62 },
    [DEXMARKERAREA_VICTORY_ROAD]     = { AREAMARKER_SQUARE,     45,   7 },
    [DEXMARKERAREA_ONE_ISLAND]       = { AREAMARKER_SQUARE,     10,  10 },
    [DEXMARKERAREA_TWO_ISLAND]       = { AREAMARKER_SQUARE,     12,  35 },
    [DEXMARKERAREA_THREE_ISLAND]     = { AREAMARKER_SQUARE,     14,  52 },
    [DEXMARKERAREA_FOUR_ISLAND]      = { AREAMARKER_SQUARE,     12,  84 },
    [DEXMARKERAREA_FIVE_ISLAND]      = { AREAMARKER_SQUARE,     45,  81 },
    [DEXMARKERAREA_SIX_ISLAND]       = { AREAMARKER_SQUARE,     76,  84 },
    [DEXMARKERAREA_SEVEN_ISLAND]     = { AREAMARKER_SQUARE,    104,  82 },
    [DEXMARKERAREA_KINDLE_ROAD]      = { AREAMARKER_V_RECT_SM,  14,   2 },
    [DEXMARKERAREA_TREASURE_BEACH]   = { AREAMARKER_SQUARE,     10,  15 },
    [DEXMARKERAREA_CAPE_BRINK]       = { AREAMARKER_SQUARE,     12,  29 },
    [DEXMARKERAREA_BOND_BRIDGE]      = { AREAMARKER_H_RECT_SM,   2,  52 },
    [DEXMARKERAREA_THREE_ISLE_PATH]  = { AREAMARKER_H_RECT_SM,  12,  56 },
    [DEXMARKERAREA_RESORT_GORGEOUS]  = { AREAMARKER_H_RECT_SM,  44,  74 },
    [DEXMARKERAREA_WATER_LABYRINTH]  = { AREAMARKER_H_RECT_SM,  36,  78 },
    [DEXMARKERAREA_FIVE_ISLE_MEADOW] = { AREAMARKER_V_RECT_SM,  48,  80 },
    [DEXMARKERAREA_MEMORIAL_PILLAR]  = { AREAMARKER_V_RECT_SM,  52,  86 },
    [DEXMARKERAREA_OUTCAST_ISLAND]   = { AREAMARKER_SQUARE,     72,  74 },
    [DEXMARKERAREA_GREEN_PATH]       = { AREAMARKER_H_RECT_SM,  72,  78 },
    [DEXMARKERAREA_WATER_PATH]       = { AREAMARKER_V_RECT_SM,  81,  80 },
    [DEXMARKERAREA_RUIN_VALLEY]      = { AREAMARKER_SQUARE,     76,  92 },
    [DEXMARKERAREA_TRAINER_TOWER]    = { AREAMARKER_SQUARE,    104,  75 },
    [DEXMARKERAREA_CANYON_ENTRANCE]  = { AREAMARKER_SQUARE,    104,  86 },
    [DEXMARKERAREA_SEVAULT_CANYON]   = { AREAMARKER_V_RECT_SM, 108,  83 },
    [DEXMARKERAREA_TANOBY_RUINS]     = { AREAMARKER_H_RECT_MD,  96,  90 },
    [DEXMARKERAREA_MT_EMBER]         = { AREAMARKER_SQUARE,     14,   1 },
    [DEXMARKERAREA_BERRY_FOREST]     = { AREAMARKER_SQUARE,      5,  52 },
    [DEXMARKERAREA_ICEFALL_CAVE]     = { AREAMARKER_SQUARE,     13,  80 },
    [DEXMARKERAREA_LOST_CAVE]        = { AREAMARKER_SQUARE,     54,  74 },
    [DEXMARKERAREA_ALTERING_CAVE]    = { AREAMARKER_SQUARE,     69,  73 },
    [DEXMARKERAREA_PATTERN_BUSH]     = { AREAMARKER_SQUARE,     76,  77 },
    [DEXMARKERAREA_DOTTED_HOLE]      = { AREAMARKER_SQUARE,     73,  95 },
    [DEXMARKERAREA_TANOBY_CHAMBERS]  = { AREAMARKER_H_RECT_MD,  96,  90 }
};

static void Task_ShowAreaMarkers(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    gSprites[data->spr_id].invisible = FALSE;
}

u8 Ctor_PokedexAreaMarkers(u16 species, u16 tilesTag, u8 palIdx, u8 y)
{
    struct SpriteTemplate spriteTemplate;
    struct CompressedSpriteSheet spriteSheet;
    u8 taskId;
    struct PAM_TaskData * data;
    struct Subsprite * subsprites;

    spriteSheet.data = sMarkerTiles;
    spriteSheet.size = 0x4A0;
    spriteSheet.tag = tilesTag;
    LoadCompressedSpriteSheet(&spriteSheet);
    LoadPalette(sMarkerPal, 0x100 + 16 * palIdx, 0x20);
    taskId = CreateTask(Task_ShowAreaMarkers, 0);
    data = (void *)gTasks[taskId].data;
    data->unk_0C = 0;
    data->tilesTag = tilesTag;
    data->unk_10 = 0xFFFF;
    subsprites = Alloc(120 * sizeof(struct Subsprite));
    data->buffer = subsprites;
    data->subsprites.subsprites = subsprites;
    data->subsprites.subspriteCount = BuildPokedexAreaSubspriteBuffer(species, subsprites);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_BD);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(12, 8));
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_CLR);
    spriteTemplate = gDummySpriteTemplate;
    spriteTemplate.tileTag = tilesTag;
    data->spr_id = CreateSprite(&spriteTemplate, 104, y + 32, 0);
    SetSubspriteTables(&gSprites[data->spr_id], &data->subsprites);
    gSprites[data->spr_id].oam.objMode = ST_OAM_OBJ_WINDOW;
    gSprites[data->spr_id].oam.paletteNum = palIdx;
    gSprites[data->spr_id].subspriteTableNum = 0;
    gSprites[data->spr_id].invisible = TRUE;
    HideBg(1);
    SetBgAttribute(1, BG_ATTR_CHARBASEINDEX, 0);
    FillBgTilemapBufferRect_Palette0(1, 0x00F, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(1);
    ShowBg(1);
    return taskId;
}

void Dtor_PokedexAreaMarkers(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    FreeSpriteTilesByTag(data->tilesTag);
    DestroySprite(&gSprites[data->spr_id]);
    Free(data->buffer);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ);
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    HideBg(1);
    SetBgAttribute(1, BG_ATTR_CHARBASEINDEX, 2);
    FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 30, 20);
    CopyBgTilemapBufferToVram(1);
    ShowBg(1);
    DestroyTask(taskId);
}

void SetAreaSubsprite(s32 i, s32 whichArea, struct Subsprite * subsprites)
{
    subsprites[i] = *sSubsprites[sSubspriteLookupTable[whichArea][0]];
    subsprites[i].x = sSubspriteLookupTable[whichArea][1];
    subsprites[i].y = sSubspriteLookupTable[whichArea][2];
}

u8 PokedexAreaMarkers_Any(u8 taskId)
{
    struct PAM_TaskData * data = (void *)gTasks[taskId].data;
    return data->subsprites.subspriteCount;
}
