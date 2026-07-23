// PURPOSE: Marks whether the current race progress has reached its target.
// Progress comes from either a two-value lookup or the active race work.
// The result is saved before the next callback is installed.
// The exact meanings of the two mode fields are uncertain.

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad_00[2];
    u8 value;
    u8 pad_03;
} ProgressValue;

typedef struct {
    u8 pad_000[0x144];
    ProgressValue values[1][2];
} ProgressLookup;

typedef struct {
    u8 pad_000[8];
    int raceMode;
    u8 pad_00c[0x10];
    int alternateMode;
    u8 pad_020[0x20];
    int progressIndex;
    u8 pad_044[0x14];
    s8 useLookup;
    u8 pad_059[7];
    u16 currentProgress;
    u8 pad_062[0x376];
    u16 targetProgress;
} RaceConfig;

typedef struct {
    u8 pad_000[0x20];
    int progressValues[8];
    int progressIndex;
    u8 pad_044[0x68];
    void (*callback)(void);
    int counter;
    int targetReached;
} ProgressWork;

extern RaceConfig *gRaceConfig;
extern ProgressLookup *data_0217aa1c;
extern ProgressWork *data_0217b3e0;
extern int GetSomeLUMaxIndex(void);
extern void func_020c13d0(void);

void func_020c0dd8(void)
{
    RaceConfig *race;
    int progress;
    int otherProgress;

    race = gRaceConfig;
    if (race->alternateMode == 1 || race->raceMode == 2) {
        if (race->useLookup != 0) {
            progress =
                data_0217aa1c->values[GetSomeLUMaxIndex()][0].value;
            otherProgress =
                data_0217aa1c->values[GetSomeLUMaxIndex()][1].value;
            if (progress <= otherProgress) {
                progress = otherProgress;
            }
        } else {
            progress = data_0217b3e0
                           ->progressValues[data_0217b3e0->progressIndex];
        }

        data_0217b3e0->targetReached =
            progress >= gRaceConfig->targetProgress;
    } else {
        data_0217b3e0->targetReached =
            race->currentProgress >= race->targetProgress;
    }

    data_0217b3e0->callback = func_020c13d0;
    data_0217b3e0->counter = 0;
}
