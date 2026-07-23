// PURPOSE: Initializes the shared sound status table for both processors.
// The argument points to the 0x280-byte sound work area.
// Player and channel status values are cleared, while variables become unused.
// The completed table is flushed so the other processor can read it.

typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct SoundPlayerSharedWork {
    s16 localVars[16];
    u32 tickCounter;
} SoundPlayerSharedWork;

typedef struct SoundSharedWork {
    u32 finishedCommandTag;
    u32 playerStatus;
    u16 channelStatus;
    u16 captureStatus;
    u8 padding_0c[0x14];
    SoundPlayerSharedWork players[16];
    s16 globalVars[16];
} SoundSharedWork;

extern void Arm_FlushRange(void *address, u32 size);

void func_020217b4(SoundSharedWork *work)
{
    work->playerStatus = 0;
    work->channelStatus = 0;
    work->captureStatus = 0;
    work->finishedCommandTag = 0;

    for (s32 i = 0; i < 16; i++) {
        work->players[i].tickCounter = 0;
        for (s32 j = 0; j < 16; j++) {
            work->players[i].localVars[j] = -1;
        }
    }

    for (s32 i = 0; i < 16; i++) {
        work->globalVars[i] = -1;
    }

    Arm_FlushRange(work, sizeof(*work));
}
