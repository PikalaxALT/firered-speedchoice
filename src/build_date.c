#include "global.h"
#include "speedchoice.h"
#include "build_date.h"

const u8 gGameVersion = GAME_VERSION;

const u8 gGameLanguage = GAME_LANGUAGE;

//#if MODERN
const char BuildDateTime[] = __DATE__ " " __TIME__;
//#else
//#if REVISION == 0
//const char BuildDateTime[] = "2004 04 26 11:20";
//#else
//const char BuildDateTime[] = "2004 07 20 09:30";
//#endif //REVISION
//#endif //MODERN

const char gSpeedchoiceVersion[] = SPEEDCHOICE_VERSION;
const u32 gRandomizerCheckValue = 0;
