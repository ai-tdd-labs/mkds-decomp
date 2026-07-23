// PURPOSE: Finalizes unfinished racers in the default race mode.
// It scans every configured racer whose finish status is still pending.
// It probably scales the shared elapsed time, converts it for display,
// and notifies the race controller that the racer has finished.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RacerFinishData {
    int status;
    u8 pad_04[0x20 - 0x04];
    u8 time[4];
    u8 pad_24[0x44 - 0x24];
    int finishScale;
    u8 pad_48[0x8c - 0x48];
} RacerFinishData;

typedef struct RaceState {
    u32 elapsedTime;
    u8 pad_04[0x0e - 0x04];
    u16 finishedRacerCount;
    u8 pad_10[0x14 - 0x10];
    RacerFinishData racers[8];
} RaceState;

typedef struct RaceConfig {
    u8 pad_00[0x08];
    int useSharedFinishTime;
    u8 pad_0c[0x3d0 - 0x0c];
    u8 racerCount;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern RaceState *data_0217561c;

extern u32 FX_Inv(void *value);
extern void MaybeConvertElapsedTime(u8 *part2, u8 *part3, u8 *part0,
                                    int part1, u32 elapsedTime);
extern void NotifyDriverFinished(RacerFinishData *racer, int value);

void RaceModeDefault_SomeFn(void)
{
    u16 racerIndex = 0;
    volatile int notifyValue;

    if ((u32)racerIndex < gRaceConfig->racerCount) {
        notifyValue = 0;

        do {
            int alreadyFinished = 0;
            int status = data_0217561c->racers[racerIndex].status;

            if (status == 1) {
                goto mark_finished;
            }
            if (status == 2) {
                goto mark_finished;
            }
            if (status != 3) {
                goto status_ready;
            }

mark_finished:
            alreadyFinished = 1;

status_ready:
            if (alreadyFinished == 0 && status != 4) {
                RacerFinishData *racer =
                    &data_0217561c->racers[racerIndex];
                u8 *time = racer->time;
                u32 elapsedTime = data_0217561c->elapsedTime;

                if (gRaceConfig->useSharedFinishTime == 0) {
                    if (racer->finishScale > 0) {
                        elapsedTime =
                            (elapsedTime *
                             FX_Inv((void *)racer->finishScale)) >> 12;
                        if (elapsedTime > 0x57e40) {
                            elapsedTime = 0x57e40;
                        }
                    } else {
                        elapsedTime = 0x57e40;
                    }
                }

                MaybeConvertElapsedTime(time + 2, time + 3, time, 0,
                                        elapsedTime);
                NotifyDriverFinished(racer, notifyValue);
            }

            racerIndex++;
        } while ((u32)racerIndex < gRaceConfig->racerCount);
    }

    data_0217561c->finishedRacerCount = gRaceConfig->racerCount;
}
