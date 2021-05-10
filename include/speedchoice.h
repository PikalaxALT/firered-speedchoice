#ifndef POKEFIRERED_SPEEDCHOICE_H
#define POKEFIRERED_SPEEDCHOICE_H

#include "constants/speedchoice.h"

// =======================================
// Global Speedchoice Configuration
// =======================================

// Maximum number of possible selectable options per option.
#define MAX_CHOICES 6

// Maximum number of options to print per page besides Start Game and Page.
#define OPTIONS_PER_PAGE 5

// Maximum number of options including Page and Start Game.
#define ALLOPTIONS_PER_PAGE OPTIONS_PER_PAGE + 2

// Number of defined pages.
#define MAX_PAGES ((CURRENT_OPTIONS_NUM + OPTIONS_PER_PAGE - 1) / OPTIONS_PER_PAGE)

// Maximum number of tile vision trainers have when Max Vision is set.
#define MAX_VISION_RANGE 8

// Number of frames per spinner iteration in Purge setting for Spinners.
#define PURGE_SPINNER_TIMER 48

// Reserved macros for a future version for a wild encounter queue system.
// Not implemented yet.
#define GRASS_QUEUE_SIZE 20
#define WATER_QUEUE_SIZE 15
#define ROCKSMASH_QUEUE_SIZE 15
#define FISHING_QUEUE_SIZE 5

/*
 * Every Speedchoice option uses a configuration to determine how to render it's options.
 * For example (Yes/No), (On/Off), etc. These Configurations determine each option's coordinate
 * to use and the string to use. Ideally I could probably do lots of fancy math to determine
 * the X as well but I'd rather just hardcode it for detailing.
 */
struct OptionChoiceConfig
{
    s32 x; // do not store the Y coordinate. Y is automatically calculated depending on the row the option is placed and therefore is not necessary.
    const u8 *string; // can be null
};

/*
 * To define an option, this global configuration struct is used to define every option that is
 * selectable or togglable.
 */
struct SpeedchoiceOption
{
    // Number of options. (2 = On/Off, etc)
    u8 optionCount;

    // see option type enumeration above.
    u8 optionType;

    // Determines if the option is enabled or not. This was used during Speedchoice development.
    bool8 enabled;

    // Pointer to the name of the option.
    const u8 *string;

    // Pointer to the array of Option configuration array. An array of MAX_CHOICES since no
    // need to define more than that. Use NULL for static options.
    const struct OptionChoiceConfig *options;

    // Pointer to Tooltip string. Printed when SELECT is pressed on the option.
    const u8 *tooltip;
};

/*
 * Before writing to the Save Block, we store the configuration in RAM temporarily before
 * flushing it to the Save Block.
 */
struct SpeedchoiceConfigStruct
{
    // The currently stored selected options per Speedchoice option. These are written
    // to the save block at the end.
    u8 optionConfig[CURRENT_OPTIONS_NUM];

    // The true ID of the selected page. This takes into account number of pages, etc.
    // If you're on Page 2, the trueIndex of the first option is 8. (7+1)
    u8 trueIndex;

    // The page ID of the option on the current page. 2nd option on page 2 is 2, etc.
    u8 pageIndex;

    // Current page number.
    u8 pageNum;
};

/*
 * In Gen 3, there is an oversight by Game Freak where upon going to a sub menu and returning
 * the spinner timers are reset due to reloading the field. Since spinners dont start trying
 * to spin until later, this oversight can be used to run past spinners safely without
 * encountering them. Because this trivializes Spinner Hell, we fix this when Hell/Why is
 * toggled by backing up the NPC timers and restoring them upon returning to the field. We skip
 * the player object's timer to avoid sprite issues.
 */
struct MapObjectTimerBackup
{
    bool8 backedUp;
    u8 spriteId;
    s16 timer;
};

/*
 * we need to extern the randomizer check value. If the ROM could see the value assigned
 * here (which is 0 by default), then it would be optimized out, but we need this location
 * to be externally written to by the randomizer.
 */
extern const u32 gRandomizerCheckValue;

// ----------------------
// Prototypes
// ----------------------
void InitSpeedchoice(MainCallback savedCallback);
u8 CheckSpeedchoiceOption(u8);
u32 CalculateCheckValue(void);

#endif // POKEFIRERED_SPEEDCHOICE_H