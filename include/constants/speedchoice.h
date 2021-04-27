#ifndef POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
#define POKEFIRERED_CONSTANTS_SPEEDCHOICE_H

#define STR_(x) #x
#define STR(x) STR_(x)

#define SPEEDCHOICE_VERSION_MAJOR         1
#define SPEEDCHOICE_VERSION_MINOR         0
#define SPEEDCHOICE_VERSION_RELSTEP       2
//#define SPEEDCHOICE_VERSION_RELEASELEVEL  a
//#define SPEEDCHOICE_VERSION_RELEASENO     0

#ifdef SPEEDCHOICE_VERSION_RELEASELEVEL
#define SPEEDCHOICE_VERSION STR(SPEEDCHOICE_VERSION_MAJOR) "." STR(SPEEDCHOICE_VERSION_MINOR) "." STR(SPEEDCHOICE_VERSION_RELSTEP) STR(SPEEDCHOICE_VERSION_RELEASELEVEL) STR(SPEEDCHOICE_VERSION_RELEASENO)
#else
#define SPEEDCHOICE_VERSION STR(SPEEDCHOICE_VERSION_MAJOR) "." STR(SPEEDCHOICE_VERSION_MINOR) "." STR(SPEEDCHOICE_VERSION_RELSTEP)
#endif

#define PRESET               0u // N/A
#define PLAYER_NAME_SET      1u // Implemented
#define EXPMATH              2u // Implemented
#define PLOTLESS             3u // Implemented
#define EARLY_SAFFRON        4u // Implemented
#define RACE_GOAL            5u // Implemented
#define INSTANTTEXT          6u // Implemented
#define SPINNERS             7u // Implemented
#define EARLYSURF            8u // Implemented
#define MAXVISION            9u // Implemented
#define NEWWILDENC          10u // Implemented
#define RUN_EVERYWHERE      11u // Implemented
#define BETTER_MARTS        12u // Implemented
#define GOOD_EARLY_WILDS    13u // Implemented
#define NICE_MENU_ORDER     14u // Implemented
#define EASY_FALSE_SWIPE    15u // Implemented
#define EASY_DEX_REWARDS    16u // Implemented
#define FAST_CATCH          17u // Implemented
#define EARLY_BIKE          18u // Implemented
#define FAST_EGG_HATCH      19u // Implemented
#define GEN_7_X_ITEMS       20u // Implemented
#define EVO_EVERY_LEVEL     21u // Implemented
#define HM_BADGE_CHECKS     22u // Implemented
#define EASY_SURGE_CANS     23u // Implemented

#define CURRENT_OPTIONS_NUM 24u
// ----------------------
// STATIC OPTIONS
// ----------------------
#define PAGE        (CURRENT_OPTIONS_NUM + 0u)
#define START_GAME  (CURRENT_OPTIONS_NUM + 1u)


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

// ---------------------
// HM_BADGE_CHECKS ENUM
// ---------------------

#define BADGE_PURGE 0
#define BADGE_KEEP 1

// --------------------
// EASY_SURGE_CANS ENUM
// --------------------
#define SURGE_NERF 0
#define SURGE_KEEP 1
#define SURGE_HELL 2
#define SURGE_WHY  3

// --------------------
// RACE GOAL ENUM
// --------------------
#define GOAL_MANUAL 0
#define GOAL_HOF    1
#define GOAL_E4R2   2

// --------------------
// EARLY SAFFRON ENUM
// --------------------
#define SAFFRON_YES 0
#define SAFFRON_NO  1

// Enumeration for optionType in the Speedchoice struct below.

#define NORMAL 0
#define ARROW 1
#define PLAYER_NAME 2

#endif //POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
