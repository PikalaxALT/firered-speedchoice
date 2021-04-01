#include "global.h"
#include "mevent.h"
#include "random.h"
#include "event_data.h"
#include "menews_jisan.h"
#include "constants/items.h"

static u32 GetMENewsJisanRewardItem(struct MENewsJisanStruct *);
static void MENewsJisanIncrementRewardCounter(struct MENewsJisanStruct *);
static u32 GetMENewsJisanState(struct MENewsJisanStruct *);
static void MENewsJisanIncrementSharedCounter(struct MENewsJisanStruct *);
static void MENewsJisanResetSharedCounter(struct MENewsJisanStruct *);

// Based on the type of event received, set a berry as a reward.
// For receiving news, you get one of these types of berry at random:
//     ITEM_RAZZ_BERRY
//     ITEM_BLUK_BERRY
//     ITEM_NANAB_BERRY
//     ITEM_WEPEAR_BERRY
//     ITEM_PINAP_BERRY
//     ITEM_POMEG_BERRY
//     ITEM_KELPSY_BERRY
//     ITEM_QUALOT_BERRY
//     ITEM_HONDEW_BERRY
//     ITEM_GREPA_BERRY
//     ITEM_TAMATO_BERRY
//     ITEM_CORNN_BERRY
//     ITEM_MAGOST_BERRY
//     ITEM_RABUTA_BERRY
//     ITEM_NOMEL_BERRY
//
// For sharing news with other people, you get one of these types of berry at random:
//     ITEM_CHERI_BERRY
//     ITEM_CHESTO_BERRY
//     ITEM_PECHA_BERRY
//     ITEM_RAWST_BERRY
//     ITEM_ASPEAR_BERRY
//     ITEM_LEPPA_BERRY
//     ITEM_ORAN_BERRY
//     ITEM_PERSIM_BERRY
//     ITEM_LUM_BERRY
//     ITEM_SITRUS_BERRY
//     ITEM_FIGY_BERRY
//     ITEM_WIKI_BERRY
//     ITEM_MAGO_BERRY
//     ITEM_AGUAV_BERRY
//     ITEM_IAPAPA_BERRY
//
// The more people are involved, the more berries you get as a reward.
void MENewsJisan_SetRandomReward(u32 type)
{
    struct MENewsJisanStruct *jisan_p = GetMENewsJisanStructPtr();

    jisan_p->state = type;
    switch (type)
    {
    case JISAN_REWARD_NONE:
        break;
    case JISAN_REWARD_RECV_FRIEND:
    case JISAN_REWARD_RECV_WIRELESS:
        jisan_p->berry = (Random() % 15) + ITEM_TO_BERRY(ITEM_RAZZ_BERRY);
        break;
    case JISAN_REWARD_SEND:
        jisan_p->berry = (Random() % 15) + ITEM_TO_BERRY(ITEM_CHERI_BERRY);
        break;
    }
}

// Initialize the news exchange state
void MENewsJisanReset(void)
{
    struct MENewsJisanStruct *jisan_p = GetMENewsJisanStructPtr();

    jisan_p->state = 0;
    jisan_p->timesShared = 0;
    jisan_p->receivedBerries = 0;
    jisan_p->berry = 0;
    VarSet(VAR_MENEWS_JISAN_STEP_COUNTER, 0);
}

// You can receive up to 5 berries. After that, you need
// to walk 500 steps (or two Max Repels' worth).
void MENewsJisanStepCounter(void)
{
    u16 *var_p = GetVarPointer(VAR_MENEWS_JISAN_STEP_COUNTER);
    struct MENewsJisanStruct *jisan_p = GetMENewsJisanStructPtr();

    if (jisan_p->receivedBerries < JISAN_REWARD_LIMIT)
        return;

    ++(*var_p);
    if (*var_p < JISAN_RESET_STEPS)
        return;

    jisan_p->receivedBerries = 0;
    *var_p = 0;
}

// Script special. Returns the reward state to the variable passed to
// the script command `specialvar`. If there is a reward to be given,
// the item id is placed in gSpecialVar_Result.
u16 GetMENewsJisanItemAndState(void)
{
    u16 *result_p = &gSpecialVar_Result;
    struct MENewsJisanStruct *jisan_p = GetMENewsJisanStructPtr();
    u16 state;

    if (!IsMysteryGiftEnabled() || !ValidateReceivedWonderNews())
        return JISAN_STATE_RECEIVED_NONE;

    state = GetMENewsJisanState(jisan_p);

    switch (state)
    {
    case JISAN_STATE_RECEIVED_NONE:
        break;
    case JISAN_STATE_RECEIVED_SINGLE:
        *result_p = GetMENewsJisanRewardItem(jisan_p);
        break;
    case JISAN_STATE_RECEIVED_MULTIPLE:
        *result_p = GetMENewsJisanRewardItem(jisan_p);
        break;
    case JISAN_STATE_SHARED_NONE:
        break;
    case JISAN_STATE_SHARED_SINGLE:
        *result_p = GetMENewsJisanRewardItem(jisan_p);
        MENewsJisanIncrementSharedCounter(jisan_p);
        break;
    case JISAN_STATE_SHARED_MULTIPLE:
        *result_p = GetMENewsJisanRewardItem(jisan_p);
        MENewsJisanResetSharedCounter(jisan_p);
        break;
    case JISAN_STATE_EXHAUSTED:
        break;
    }

    return state;
}

// Retrieves the stored reward and prepares the internal state to
// receive more news.
static u32 GetMENewsJisanRewardItem(struct MENewsJisanStruct *jisan_p)
{
    u32 item_id;

    jisan_p->state = JISAN_REWARD_NONE;
    item_id = jisan_p->berry + FIRST_BERRY_INDEX - 1;
    jisan_p->berry = 0;
    MENewsJisanIncrementRewardCounter(jisan_p);
    return item_id;
}

// Resets the counter which keeps track of how many times news was shared.
static void MENewsJisanResetSharedCounter(struct MENewsJisanStruct *jisan_p)
{
    jisan_p->timesShared = 0;
}

// Capped increment for the counter described above.
static void MENewsJisanIncrementSharedCounter(struct MENewsJisanStruct *jisan_p)
{
    jisan_p->timesShared++;
    if (jisan_p->timesShared > JISAN_SHARED_LIMIT)
        jisan_p->timesShared = JISAN_SHARED_LIMIT;
}

// Capped increment for the counter which tracks how many times berries were
// received.
static void MENewsJisanIncrementRewardCounter(struct MENewsJisanStruct *jisan_p)
{
    jisan_p->receivedBerries++;
    if (jisan_p->receivedBerries > JISAN_REWARD_LIMIT)
        jisan_p->receivedBerries = JISAN_REWARD_LIMIT;
}

// Based on what type of reward was received, returns the state value
// to be reported to the script command handler.
static u32 GetMENewsJisanState(struct MENewsJisanStruct *jisan_p)
{
    if (jisan_p->receivedBerries == JISAN_REWARD_LIMIT)
        return JISAN_STATE_EXHAUSTED;

    switch (jisan_p->state)
    {
    case JISAN_REWARD_NONE:
        return JISAN_STATE_SHARED_NONE;
    case JISAN_REWARD_RECV_FRIEND:
        return JISAN_STATE_RECEIVED_SINGLE;
    case JISAN_REWARD_RECV_WIRELESS:
        return JISAN_STATE_RECEIVED_MULTIPLE;
    case JISAN_REWARD_SEND:
        if (jisan_p->timesShared < 3)
            return JISAN_STATE_SHARED_SINGLE;
        else
            return JISAN_STATE_SHARED_MULTIPLE;
    default:
        AGB_ASSERT_EX(0, ABSPATH("menews_jisan.c"), 383);
        return 0;
    }
}
