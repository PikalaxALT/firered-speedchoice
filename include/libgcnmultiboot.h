#ifndef GUARD_LIBGCNMULTIBOOT_H
#define GUARD_LIBGCNMULTIBOOT_H

#define MBPROGRESS_NONE                0
#define MBPROGRESS_LOGO_CORRECT        1
#define MBPROGRESS_READY_TO_BOOT       2

struct GcmbStruct
{
    vu8 counter1;
    vu8 counter2;
    vu8 mbProgress;
    vu8 savedVcount;
    vu32 keyA;
    vu32 keyB;
    vu32 keyC;
    vu16 bootKey;
    vu16 imageSize;
    vu32 sessionKey;
    vu32 hashVal;
    vu32 keyCderivation;
    u32 * volatile baseDestPtr;
    u32 * volatile curDestPtr;
    void (* volatile serialIntrHandler)(struct GcmbStruct *, u32);
};

void GameCubeMultiBoot_Main(struct GcmbStruct *pStruct);
void GameCubeMultiBoot_ExecuteProgram(struct GcmbStruct *pStruct);
void GameCubeMultiBoot_Init(struct GcmbStruct *pStruct);
void GameCubeMultiBoot_HandleSerialInterrupt(struct GcmbStruct *pStruct);
void GameCubeMultiBoot_Quit(void);

#endif // GUARD_LIBGCNMULTIBOOT_H
