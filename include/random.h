#ifndef GUARD_RANDOM_H
#define GUARD_RANDOM_H

#include "global.h"

extern u32 gRngValue;
extern u32 gRng2Value;

#define LC_MUL 1103515245
#define LC_INC 24691
#define LC_RNG(seed) (LC_MUL * (seed) + LC_INC)

//Returns a 16-bit pseudorandom number
u16 Random(void);
u16 Random2(void);

//Returns a 32-bit pseudorandom number
#define Random32() (Random() | (Random() << 16))

//Sets the initial seed value of the pseudorandom number generator
void SeedRng(u16 seed);
void SeedRng2(u16 seed);

#endif // GUARD_RANDOM_H
