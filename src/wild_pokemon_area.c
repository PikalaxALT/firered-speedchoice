#include "global.h"
#include "field_specials.h"
#include "event_data.h"
#include "wild_encounter.h"
#include "roamer.h"
#include "overworld.h"
#include "pokedex_area_markers.h"
#include "constants/region_map_sections.h"

struct SeviiDexArea
{
    const u16 (*lut)[2];
    s32 count;
};

struct RoamerPair
{
    u16 roamer;
    u16 starter;
};

static s32 GetRoamerIndex(u16 species);
static s32 CountRoamerNests(u16 species, struct Subsprite * subsprites);
static bool32 PokemonInAnyEncounterTableInMap(const struct WildPokemonHeader * data, s32 species);
static bool32 PokemonInEncounterTable(const struct WildPokemonInfo * pokemon, s32 species, s32 count);
static u16 GetMapSecIdFromWildMonHeader(const struct WildPokemonHeader * header);
static bool32 TryGetMapSecPokedexAreaEntry(u16 mapSecId, const u16 (*lut)[2], s32 count, s32 * lutIdx_p, u16 * tableIdx_p);

static const u16 sDexAreas_Kanto[][2] = {
    { MAPSEC_PALLET_TOWN,         DEXMARKERAREA_PALLET_TOWN },
    { MAPSEC_VIRIDIAN_CITY,       DEXMARKERAREA_VIRIDIAN_CITY },
    { MAPSEC_PEWTER_CITY,         DEXMARKERAREA_PEWTER_CITY },
    { MAPSEC_CERULEAN_CITY,       DEXMARKERAREA_CERULEAN_CITY },
    { MAPSEC_LAVENDER_TOWN,       DEXMARKERAREA_LAVENDER_TOWN },
    { MAPSEC_VERMILION_CITY,      DEXMARKERAREA_VERMILION_CITY },
    { MAPSEC_CELADON_CITY,        DEXMARKERAREA_CELADON_CITY },
    { MAPSEC_FUCHSIA_CITY,        DEXMARKERAREA_FUCHSIA_CITY },
    { MAPSEC_CINNABAR_ISLAND,     DEXMARKERAREA_CINNABAR_ISLAND },
    { MAPSEC_INDIGO_PLATEAU,      DEXMARKERAREA_INDIGO_PLATEAU },
    { MAPSEC_SAFFRON_CITY,        DEXMARKERAREA_SAFFRON_CITY },
    { MAPSEC_ROUTE_4_POKECENTER,  DEXMARKERAREA_ROUTE_4 },
    { MAPSEC_ROUTE_10_POKECENTER, DEXMARKERAREA_ROUTE_10 },
    { MAPSEC_ROUTE_1,             DEXMARKERAREA_ROUTE_1 },
    { MAPSEC_ROUTE_2,             DEXMARKERAREA_ROUTE_2 },
    { MAPSEC_ROUTE_3,             DEXMARKERAREA_ROUTE_3 },
    { MAPSEC_ROUTE_4,             DEXMARKERAREA_ROUTE_4 },
    { MAPSEC_ROUTE_5,             DEXMARKERAREA_ROUTE_5 },
    { MAPSEC_ROUTE_6,             DEXMARKERAREA_ROUTE_6 },
    { MAPSEC_ROUTE_7,             DEXMARKERAREA_ROUTE_7 },
    { MAPSEC_ROUTE_8,             DEXMARKERAREA_ROUTE_8 },
    { MAPSEC_ROUTE_9,             DEXMARKERAREA_ROUTE_9 },
    { MAPSEC_ROUTE_10,            DEXMARKERAREA_ROUTE_10 },
    { MAPSEC_ROUTE_11,            DEXMARKERAREA_ROUTE_11 },
    { MAPSEC_ROUTE_12,            DEXMARKERAREA_ROUTE_12 },
    { MAPSEC_ROUTE_13,            DEXMARKERAREA_ROUTE_13 },
    { MAPSEC_ROUTE_14,            DEXMARKERAREA_ROUTE_14 },
    { MAPSEC_ROUTE_15,            DEXMARKERAREA_ROUTE_15 },
    { MAPSEC_ROUTE_16,            DEXMARKERAREA_ROUTE_16 },
    { MAPSEC_ROUTE_17,            DEXMARKERAREA_ROUTE_17 },
    { MAPSEC_ROUTE_18,            DEXMARKERAREA_ROUTE_18 },
    { MAPSEC_ROUTE_19,            DEXMARKERAREA_ROUTE_19 },
    { MAPSEC_ROUTE_20,            DEXMARKERAREA_ROUTE_20 },
    { MAPSEC_ROUTE_21,            DEXMARKERAREA_ROUTE_21 },
    { MAPSEC_ROUTE_22,            DEXMARKERAREA_ROUTE_22 },
    { MAPSEC_ROUTE_23,            DEXMARKERAREA_ROUTE_23 },
    { MAPSEC_ROUTE_24,            DEXMARKERAREA_ROUTE_24 },
    { MAPSEC_ROUTE_25,            DEXMARKERAREA_ROUTE_25 },
    { MAPSEC_VIRIDIAN_FOREST,     DEXMARKERAREA_VIRIDIAN_FOREST },
    { MAPSEC_MT_MOON,             DEXMARKERAREA_MT_MOON },
    { MAPSEC_S_S_ANNE,            DEXMARKERAREA_VERMILION_CITY },
    { MAPSEC_UNDERGROUND_PATH,    DEXMARKERAREA_SAFFRON_CITY },
    { MAPSEC_UNDERGROUND_PATH_2,  DEXMARKERAREA_SAFFRON_CITY },
    { MAPSEC_DIGLETTS_CAVE,       DEXMARKERAREA_DIGLETTS_CAVE },
    { MAPSEC_KANTO_VICTORY_ROAD,  DEXMARKERAREA_VICTORY_ROAD },
    { MAPSEC_ROCKET_HIDEOUT,      DEXMARKERAREA_CELADON_CITY },
    { MAPSEC_SILPH_CO,            DEXMARKERAREA_SAFFRON_CITY },
    { MAPSEC_POKEMON_MANSION,     DEXMARKERAREA_POKEMON_MANSION },
    { MAPSEC_KANTO_SAFARI_ZONE,   DEXMARKERAREA_SAFARI_ZONE },
    { MAPSEC_POKEMON_LEAGUE,      DEXMARKERAREA_VICTORY_ROAD },
    { MAPSEC_ROCK_TUNNEL,         DEXMARKERAREA_ROCK_TUNNEL },
    { MAPSEC_SEAFOAM_ISLANDS,     DEXMARKERAREA_SEAFOAM_ISLANDS },
    { MAPSEC_POKEMON_TOWER,       DEXMARKERAREA_POKEMON_TOWER },
    { MAPSEC_CERULEAN_CAVE,       DEXMARKERAREA_CERULEAN_CAVE },
    { MAPSEC_POWER_PLANT,         DEXMARKERAREA_POWER_PLANT }
};

static const u16 sDexAreas_Sevii1[][2] = {
	{ MAPSEC_KINDLE_ROAD,    DEXMARKERAREA_KINDLE_ROAD },
	{ MAPSEC_TREASURE_BEACH, DEXMARKERAREA_TREASURE_BEACH },
	{ MAPSEC_ONE_ISLAND,     DEXMARKERAREA_ONE_ISLAND },
	{ MAPSEC_MT_EMBER,       DEXMARKERAREA_MT_EMBER }
};

static const u16 sDexAreas_Sevii2[][2] = {
	{ MAPSEC_CAPE_BRINK, DEXMARKERAREA_CAPE_BRINK },
	{ MAPSEC_TWO_ISLAND, DEXMARKERAREA_TWO_ISLAND }
};

static const u16 sDexAreas_Sevii3[][2] = {
	{ MAPSEC_BOND_BRIDGE,     DEXMARKERAREA_BOND_BRIDGE },
	{ MAPSEC_THREE_ISLE_PORT, DEXMARKERAREA_THREE_ISLE_PATH },
	{ MAPSEC_THREE_ISLAND,    DEXMARKERAREA_THREE_ISLAND },
	{ MAPSEC_BERRY_FOREST,    DEXMARKERAREA_BERRY_FOREST },
	{ MAPSEC_THREE_ISLE_PATH, DEXMARKERAREA_THREE_ISLE_PATH }
};

static const u16 sDexAreas_Sevii4[][2] = {
	{ MAPSEC_FOUR_ISLAND,  DEXMARKERAREA_FOUR_ISLAND },
	{ MAPSEC_ICEFALL_CAVE, DEXMARKERAREA_ICEFALL_CAVE }
};

static const u16 sDexAreas_Sevii5[][2] = {
	{ MAPSEC_RESORT_GORGEOUS,  DEXMARKERAREA_RESORT_GORGEOUS },
	{ MAPSEC_WATER_LABYRINTH,  DEXMARKERAREA_WATER_LABYRINTH },
	{ MAPSEC_FIVE_ISLE_MEADOW, DEXMARKERAREA_FIVE_ISLE_MEADOW },
	{ MAPSEC_MEMORIAL_PILLAR,  DEXMARKERAREA_MEMORIAL_PILLAR },
	{ MAPSEC_FIVE_ISLAND,      DEXMARKERAREA_FIVE_ISLAND },
	{ MAPSEC_ROCKET_WAREHOUSE, DEXMARKERAREA_FIVE_ISLE_MEADOW },
	{ MAPSEC_LOST_CAVE,        DEXMARKERAREA_LOST_CAVE }
};

static const u16 sDexAreas_Sevii6[][2] = {
	{ MAPSEC_OUTCAST_ISLAND, DEXMARKERAREA_OUTCAST_ISLAND },
	{ MAPSEC_GREEN_PATH,     DEXMARKERAREA_GREEN_PATH },
	{ MAPSEC_WATER_PATH,     DEXMARKERAREA_WATER_PATH },
	{ MAPSEC_RUIN_VALLEY,    DEXMARKERAREA_RUIN_VALLEY },
	{ MAPSEC_DOTTED_HOLE,    DEXMARKERAREA_DOTTED_HOLE },
	{ MAPSEC_PATTERN_BUSH,   DEXMARKERAREA_PATTERN_BUSH },
	{ MAPSEC_ALTERING_CAVE,  DEXMARKERAREA_ALTERING_CAVE }
};

static const u16 sDexAreas_Sevii7[][2] = {
	{ MAPSEC_TRAINER_TOWER,   DEXMARKERAREA_TRAINER_TOWER },
	{ MAPSEC_CANYON_ENTRANCE, DEXMARKERAREA_CANYON_ENTRANCE },
	{ MAPSEC_SEVAULT_CANYON,  DEXMARKERAREA_SEVAULT_CANYON },
	{ MAPSEC_TANOBY_RUINS,    DEXMARKERAREA_TANOBY_RUINS },
	{ MAPSEC_MONEAN_CHAMBER,  DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_LIPTOO_CHAMBER,  DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_WEEPTH_CHAMBER,  DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_DILFORD_CHAMBER, DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_SCUFIB_CHAMBER,  DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_RIXY_CHAMBER,    DEXMARKERAREA_TANOBY_CHAMBERS },
	{ MAPSEC_VIAPOIS_CHAMBER, DEXMARKERAREA_TANOBY_CHAMBERS }
};

static const struct SeviiDexArea sSeviiDexAreas[] = {
    { sDexAreas_Sevii1, NELEMS(sDexAreas_Sevii1) },
    { sDexAreas_Sevii2, NELEMS(sDexAreas_Sevii2) },
    { sDexAreas_Sevii3, NELEMS(sDexAreas_Sevii3) },
    { sDexAreas_Sevii4, NELEMS(sDexAreas_Sevii4) },
    { sDexAreas_Sevii5, NELEMS(sDexAreas_Sevii5) },
    { sDexAreas_Sevii6, NELEMS(sDexAreas_Sevii6) },
    { sDexAreas_Sevii7, NELEMS(sDexAreas_Sevii7) }
};

static const struct RoamerPair sRoamerPairs[] = {
    { SPECIES_ENTEI,   SPECIES_BULBASAUR  },
    { SPECIES_SUICUNE, SPECIES_CHARMANDER },
    { SPECIES_RAIKOU,  SPECIES_SQUIRTLE   }
};

// Speedchoice change: Set up for dex sound
EWRAM_DATA static bool8 sInSameMap = 0;

s32 BuildPokedexAreaSubspriteBuffer(u16 species, struct Subsprite * subsprites)
{
    s32 areaCount = 0;
    s32 j;
    s32 mapSecId;
    u16 dexAreaSubspriteIdx;
    s32 dexAreaEntryLUTidx;
    s32 seviiAreas;
//    s32 alteringCaveCount;
//    s32 alteringCaveNum;
    s32 i;

    sInSameMap = FALSE;

    if (GetRoamerIndex(species) >= 0)
    {
        areaCount = CountRoamerNests(species, subsprites);
    }

    seviiAreas = GetUnlockedSeviiAreas();
    // Speedchoice change: Ignore Altering Cave
//    alteringCaveCount = 0;
//    alteringCaveNum = VarGet(VAR_ALTERING_CAVE_WILD_SET);
//    if (alteringCaveNum > 8)
//        alteringCaveNum = 0;
    for (i = 0; gWildMonHeaders[i].mapGroup != 0xFF; i++)
    {
        mapSecId = GetMapSecIdFromWildMonHeader(&gWildMonHeaders[i]);
//        if (mapSecId == MAPSEC_ALTERING_CAVE)
//        {
//            alteringCaveCount++;
//            if (alteringCaveNum != alteringCaveCount - 1)
//                continue;
//        }
        if (PokemonInAnyEncounterTableInMap(&gWildMonHeaders[i], species))
        {
            dexAreaEntryLUTidx = 0;
            while (TryGetMapSecPokedexAreaEntry(mapSecId, sDexAreas_Kanto, NELEMS(sDexAreas_Kanto), &dexAreaEntryLUTidx, &dexAreaSubspriteIdx))
            {
                if (dexAreaSubspriteIdx != 0)
                {
                    SetAreaSubsprite(areaCount++, dexAreaSubspriteIdx, subsprites);
                }
            }
            for (j = 0; j < NELEMS(sSeviiDexAreas); j++)
            {
                if ((seviiAreas >> j) & 1)
                {
                    dexAreaEntryLUTidx = 0;
                    while (TryGetMapSecPokedexAreaEntry(mapSecId, sSeviiDexAreas[j].lut, sSeviiDexAreas[j].count, &dexAreaEntryLUTidx, &dexAreaSubspriteIdx))
                    {
                        if (dexAreaSubspriteIdx != 0)
                        {
                            SetAreaSubsprite(areaCount++, dexAreaSubspriteIdx, subsprites);
                        }
                    }
                }
            }
            if (gWildMonHeaders[i].mapGroup == gSaveBlock1Ptr->location.mapGroup && gWildMonHeaders[i].mapNum == gSaveBlock1Ptr->location.mapNum)
            {
                sInSameMap = TRUE;
            }
        }
    }

    return areaCount;
}

bool8 InSameMapAsWildMon(void)
{
    return sInSameMap;
}

static s32 GetRoamerIndex(u16 species)
{
    s32 i;
    for (i = 0; i < NELEMS(sRoamerPairs); i++)
    {
        if (sRoamerPairs[i].roamer == species)
            return i;
    }

    return -1;
}

static s32 CountRoamerNests(u16 species, struct Subsprite * subsprites)
{
    u16 roamerLocation;
    s32 roamerIdx;
    u16 dexAreaSubspriteIdx;
    s32 dexAreaEntryLUTidx;

    roamerIdx = GetRoamerIndex(species);
    if (roamerIdx < 0)
        return 0;
    if (sRoamerPairs[roamerIdx].starter != GetStarterSpecies())
        return 0;
    roamerLocation = GetRoamerLocationMapSectionId();
    dexAreaEntryLUTidx = 0;
    if (TryGetMapSecPokedexAreaEntry(roamerLocation, sDexAreas_Kanto, 55, &dexAreaEntryLUTidx, &dexAreaSubspriteIdx))
    {
        if (dexAreaSubspriteIdx != 0)
        {
            SetAreaSubsprite(0, dexAreaSubspriteIdx, subsprites);
            return 1;
        }
    }
    return 0;
}

static bool32 PokemonInAnyEncounterTableInMap(const struct WildPokemonHeader * data, s32 species)
{
    if (PokemonInEncounterTable(data->landMonsInfo, species, 12))
        return TRUE;
    if (PokemonInEncounterTable(data->waterMonsInfo, species, 5))
        return TRUE;
    if (PokemonInEncounterTable(data->fishingMonsInfo, species, 12)) // 10
        return TRUE;
    if (PokemonInEncounterTable(data->rockSmashMonsInfo, species, 5))
        return TRUE;

    return FALSE;
}

static bool32 PokemonInEncounterTable(const struct WildPokemonInfo * info, s32 species, s32 count)
{
    s32 i;
    if (info != NULL)
    {
        for (i = 0; i < count; i++)
        {
            if (info->wildPokemon[i].species == species)
                return TRUE;
        }
    }
    return FALSE;
}

static u16 GetMapSecIdFromWildMonHeader(const struct WildPokemonHeader * header)
{
    return Overworld_GetMapHeaderByGroupAndId(header->mapGroup, header->mapNum)->regionMapSectionId;
}

static bool32 TryGetMapSecPokedexAreaEntry(u16 mapSecId, const u16 (*lut)[2], s32 count, s32 * lutIdx_p, u16 * tableIdx_p)
{
    s32 i;
    for (i = *lutIdx_p; i < count; i++)
    {
        if (lut[i][0] == mapSecId)
        {
            *tableIdx_p = lut[i][1];
            *lutIdx_p = i + 1;
            return TRUE;
        }
    }
    return FALSE;
}
