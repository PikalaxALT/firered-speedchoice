#ifndef GUARD_MENEWS_JISAN_H
#define GUARD_MENEWS_JISAN_H

#include "global.h"

#define JISAN_STATE_RECEIVED_NONE      0
#define JISAN_STATE_RECEIVED_SINGLE    1
#define JISAN_STATE_RECEIVED_MULTIPLE  2 // gives 4
#define JISAN_STATE_SHARED_NONE        3
#define JISAN_STATE_SHARED_SINGLE      4
#define JISAN_STATE_SHARED_MULTIPLE    5 // gives 4
#define JISAN_STATE_EXHAUSTED          6

#define JISAN_REWARD_NONE              0
#define JISAN_REWARD_RECV_FRIEND       1
#define JISAN_REWARD_RECV_WIRELESS     2
#define JISAN_REWARD_SEND              3

#define JISAN_SHARED_LIMIT     4
#define JISAN_REWARD_LIMIT     5
#define JISAN_RESET_STEPS    500

void MENewsJisan_SetRandomReward(u32 type);
void MENewsJisanReset(void);
void MENewsJisanStepCounter(void);

#endif //GUARD_MENEWS_JISAN_H
