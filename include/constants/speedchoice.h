#ifndef POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
#define POKEFIRERED_CONSTANTS_SPEEDCHOICE_H

#define PRESET               0 // N/A
#define PLAYER_NAME_SET      1 // Implemented
#define EXPMATH              2 // Implemented
#define PLOTLESS             3 // TODO
#define INSTANTTEXT          4 // Implemented
#define SPINNERS             5 // Implemented
#define EARLYSURF            6 // TODO
#define MAXVISION            7 // Implemented
#define NEWWILDENC           8 // TODO
#define RUN_EVERYWHERE       9 // Implemented
#define BETTER_MARTS        10 // Implemented
#define GOOD_EARLY_WILDS    11 // TODO
#define NICE_MENU_ORDER     12 // Implemented
#define EASY_FALSE_SWIPE    13 // Implemented
#define EASY_DEX_REWARDS    14 // Implemented
#define FAST_CATCH          15 // TODO
#define EARLY_BIKE          16 // Implemented
#define FAST_EGG_HATCH      17 // TODO
#define GEN_7_X_ITEMS       18 // TODO
#define EVO_EVERY_LEVEL     19 // TODO

#define CURRENT_OPTIONS_NUM 20
// ----------------------
// STATIC OPTIONS
// ----------------------
#define PAGE        20
#define START_GAME  21


/*
 * Enumerations for GetPageOptionTrueIndex. When passing this, the function will
 * return the true index from that page given whether you are specifying the first
 * option of the page or the last one.
 */

#define FIRST 0
#define LAST 1

// We used to share the enums for options, but we don't anymore because it's confusing
// as fuck. Please define enums for each option and have them match the option config.

// ----------------------
// EXP ENUM
// ----------------------

#define EXP_KEEP 0
#define EXP_BW 1
#define EXP_NONE 2

// ----------------------
// PLOTLESS ENUM
// ----------------------

#define PLOT_SEMI 0
#define PLOT_KEEP 1
#define PLOT_FULL 2

// ----------------------
// INSTANT TEXT ENUM
// ----------------------

#define IT_ON 0
#define IT_OFF 1

// ----------------------
// EARLY SURF ENUM
// ----------------------

#define EARLY_SURF_YES 0
#define EARLY_SURF_NO  1

// ----------------------
// SPINNERS ENUM
// ----------------------

#define SPIN_NERF 0
#define SPIN_KEEP 1
#define SPIN_HELL 2
#define SPIN_WHY 3

// ----------------------
// MAX VISION ENUM
// ----------------------

#define MAX_OFF 0
#define MAX_SANE 1
#define MAX_HELL 2

// ----------------------
// NEW WILD ENC ENUM
// ----------------------

#define NEW_ON 0
#define NEW_OFF 1

// ----------------------
// RUN EVERYWHERE ENUM
// ----------------------

#define RUN_ON 0
#define RUN_OFF 1

// ----------------------
// BETTER MARTS ENUM
// ----------------------

#define MARTS_ON 0
#define MARTS_OFF 1

// ----------------------
// GOOD EARLY WILDS ENUM
// ----------------------

#define GOOD_OFF 0
#define GOOD_STATIC 1
#define GOOD_RAND 2

// ----------------------
// PARTY MENU ENUM
// ----------------------

#define NICE_MENU_ORDER_ON 0
#define NICE_MENU_ORDER_OFF 1

// ----------------------
// EASY FALSE SWIPE ENUM
// ----------------------

#define EASY_FALSE_SWIPE_OFF 0
#define EASY_FALSE_SWIPE_TUTOR 1
#define EASY_FALSE_SWIPE_HM05 2

// ----------------------
// EASY DEX REWARDS ENUM
// ----------------------

#define EASY_DEX_REWARDS_ON 0
#define EASY_DEX_REWARDS_OFF 1

// ----------------------
// FAST CATCH ENUM
// ----------------------

#define FAST_CATCH_ON 0
#define FAST_CATCH_OFF 1

// ----------------------
// EARLY BIKE ENUM
// ----------------------

#define EARLY_BIKE_YES 0
#define EARLY_BIKE_NO 1

// ----------------------
// FAST EGG HATCHING ENUM
// ----------------------

#define FAST_EGG_HATCH_YES 0
#define FAST_EGG_HATCH_NO 1
// ----------------------
// GEN 7 X ITEMS ENUM
// ----------------------

#define GEN_7_X_ITEMS_ON 0
#define GEN_7_X_ITEMS_OFF 1

// ----------------------
// EVO_EVERY_LEVEL ENUM
// ----------------------

#define EVO_EV_OFF 0
#define EVO_EV_STATIC 1
#define EVO_EV_RAND 2

// Enumeration for optionType in the Speedchoice struct below.

#define NORMAL 0
#define ARROW 1
#define PLAYER_NAME 2

#endif //POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
