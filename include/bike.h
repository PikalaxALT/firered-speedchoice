#ifndef GUARD_BIKE_H
#define GUARD_BIKE_H

// TODO: Do the constants make sense in FRLG? 

// Player speeds
enum
{
    SPEED_STANDING,
    SPEED_NORMAL,
    SPEED_FAST,
    SPEED_FASTER,
    SPEED_FASTEST,
};

// mach bike transitions enum
enum
{
    MACH_TRANS_FACE_DIRECTION,
    MACH_TRANS_TURN_DIRECTION,
    MACH_TRANS_KEEP_MOVING,
    MACH_TRANS_START_MOVING
};

// Acro bike states
enum
{
    BIKE_STATE_NORMAL,
    BIKE_STATE_TURNING,
    BIKE_STATE_DOWNHILL,
};

void BikeClearState(u32 directionHistory, u32 abStartSelectHistory);
bool8 IsBikingDisallowedByPlayer(void);
void GetOnOffBike(u8 flags);
s16 GetPlayerSpeed(void);
bool8 RS_IsRunningDisallowed(u8);
void MovePlayerOnBike(u8 direction, u16 newKeys, u16 heldKeys);
bool32 IsRunningDisallowed(u8 metatileBehavior);
void Bike_HandleBumpySlopeJump(void);
void Bike_UpdateBikeCounterSpeed(u8 counter);
bool8 IsPlayerNotUsingAcroBikeOnBumpySlope(void);

#endif //GUARD_BIKE_H
