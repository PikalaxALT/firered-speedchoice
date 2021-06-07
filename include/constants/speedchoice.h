#ifndef POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
#define POKEFIRERED_CONSTANTS_SPEEDCHOICE_H

#define STR_(x) #x
#define STR(x) STR_(x)

#define SPEEDCHOICE_VERSION_MAJOR         1
#define SPEEDCHOICE_VERSION_MINOR         1
#define SPEEDCHOICE_VERSION_RELSTEP       3
//#define SPEEDCHOICE_VERSION_RELEASELEVEL  a
//#define SPEEDCHOICE_VERSION_RELEASENO     0

#ifdef SPEEDCHOICE_VERSION_RELEASELEVEL
#define SPEEDCHOICE_VERSION STR(SPEEDCHOICE_VERSION_MAJOR) "." STR(SPEEDCHOICE_VERSION_MINOR) "." STR(SPEEDCHOICE_VERSION_RELSTEP) STR(SPEEDCHOICE_VERSION_RELEASELEVEL) STR(SPEEDCHOICE_VERSION_RELEASENO)
#else
#define SPEEDCHOICE_VERSION STR(SPEEDCHOICE_VERSION_MAJOR) "." STR(SPEEDCHOICE_VERSION_MINOR) "." STR(SPEEDCHOICE_VERSION_RELSTEP)
#endif

#define PRESET               0
#define PLAYER_NAME_SET      1
#define EXPMATH              2
#define PLOTLESS             3
#define EARLY_SAFFRON        4
#define RACE_GOAL            5
#define SPINNERS             6
#define EARLYSURF            7
#define MAXVISION            8
#define GOOD_EARLY_WILDS     9
#define EASY_FALSE_SWIPE    10
#define EASY_DEX_REWARDS    11
#define FAST_CATCH          12
#define EARLY_BIKE          13
#define GEN_7_X_ITEMS       14
#define EVO_EVERY_LEVEL     15
#define HM_BADGE_CHECKS     16
#define EASY_SURGE_CANS     17
#define NERF_BROCK          18

#define CURRENT_OPTIONS_NUM 19
// ----------------------
// STATIC OPTIONS
// ----------------------
#define PAGE        (CURRENT_OPTIONS_NUM + 0)
#define START_GAME  (CURRENT_OPTIONS_NUM + 1)


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
#define EXP_OPTION_COUNT 3

// ----------------------
// PLOTLESS ENUM
// ----------------------

#define PLOT_SEMI 0
#define PLOT_KEEP 1
#define PLOT_FULL 2
#define PLOT_OPTION_COUNT 3

// ----------------------
// EARLY SURF ENUM
// ----------------------

#define EARLY_SURF_YES 0
#define EARLY_SURF_NO  1
#define EARLY_SURF_OPTION_COUNT 2

// ----------------------
// SPINNERS ENUM
// ----------------------

#define SPIN_NERF 0
#define SPIN_KEEP 1
#define SPIN_HELL 2
#define SPIN_WHY 3
#define SPIN_OPTION_COUNT 4

// ----------------------
// MAX VISION ENUM
// ----------------------

#define MAX_OFF 0
#define MAX_SANE 1
#define MAX_HELL 2
#define MAX_OPTION_COUNT 3

// ----------------------
// GOOD EARLY WILDS ENUM
// ----------------------

#define GOOD_OFF 0
#define GOOD_STATIC 1
#define GOOD_RAND 2
#define GOOD_OPTION_COUNT 3

// ----------------------
// EASY FALSE SWIPE ENUM
// ----------------------

#define EASY_FALSE_SWIPE_OFF 0
#define EASY_FALSE_SWIPE_TUTOR 1
#define EASY_FALSE_SWIPE_HM05 2
#define EASY_FALSE_SWIPE_OPTION_COUNT 3

// ----------------------
// EASY DEX REWARDS ENUM
// ----------------------

#define EASY_DEX_REWARDS_ON 0
#define EASY_DEX_REWARDS_OFF 1
#define EASY_DEX_REWARDS_OPTION_COUNT 2

// ----------------------
// FAST CATCH ENUM
// ----------------------

#define FAST_CATCH_ON 0
#define FAST_CATCH_OFF 1
#define FAST_CATCH_OPTION_COUNT 2

// ----------------------
// EARLY BIKE ENUM
// ----------------------

#define EARLY_BIKE_YES 0
#define EARLY_BIKE_NO 1
#define EARLY_BIKE_OPTION_COUNT 2

// ----------------------
// GEN 7 X ITEMS ENUM
// ----------------------

#define GEN_7_X_ITEMS_ON 0
#define GEN_7_X_ITEMS_OFF 1
#define GEN_7_X_ITEMS_OPTION_COUNT 2

// ----------------------
// EVO_EVERY_LEVEL ENUM
// ----------------------

#define EVO_EV_OFF 0
#define EVO_EV_STATIC 1
#define EVO_EV_RAND 2
#define EVO_EV_OPTION_COUNT 3

// ---------------------
// HM_BADGE_CHECKS ENUM
// ---------------------

#define BADGE_PURGE 0
#define BADGE_KEEP 1
#define BADGE_OPTION_COUNT 2

// --------------------
// EASY_SURGE_CANS ENUM
// --------------------
#define SURGE_NERF 0
#define SURGE_KEEP 1
#define SURGE_HELL 2
#define SURGE_WHY  3
#define SURGE_OPTION_COUNT 4

// --------------------
// RACE GOAL ENUM
// --------------------
#define GOAL_MANUAL 0
#define GOAL_HOF    1
#define GOAL_E4R2   2
#define GOAL_OPTION_COUNT 3

// --------------------
// EARLY SAFFRON ENUM
// --------------------
#define SAFFRON_YES 0
#define SAFFRON_NO  1
#define SAFFRON_OPTION_COUNT 2

// --------------------
// NERF BROCK ENUM
// --------------------
#define NERF_YES 0
#define NERF_NO  1
#define NERF_OPTION_COUNT 2

// Enumeration for optionType in the Speedchoice struct below.

#define NORMAL 0
#define ARROW 1
#define PLAYER_NAME 2

#endif //POKEFIRERED_CONSTANTS_SPEEDCHOICE_H
