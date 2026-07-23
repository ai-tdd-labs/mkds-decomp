// PURPOSE: Finds a racer's fastest completed lap.
// The racer index selects the timing record to scan.
// The three output pointers receive minutes, seconds, and milliseconds.
// The return value is the one-based index of the latest equally fast lap.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct LapTime {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
} LapTime;

typedef struct RacerTimingRecord {
    u8 unknown_00[0x20];
    LapTime lapTimes[3];
    u8 unknown_2c[0x60];
} RacerTimingRecord;

typedef struct RaceLapSettings {
    u16 unknown_00;
    u16 lapCount;
} RaceLapSettings;

typedef struct RaceTimingState {
    u8 unknown_00[0x18];
    RaceLapSettings *lapSettings;
} RaceTimingState;

extern RacerTimingRecord *data_0217561c;
extern RaceTimingState *data_02175620;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int GetLeastTimeLap(int racerId, u8 *minutes, u8 *seconds,
                    u16 *milliseconds)
{
    int leastLap = 1;
    int firstLap = 1;
    u16 lap = 1;
    int one = 1;
    LapTime leastTime;

    if (data_02175620->lapSettings->lapCount >= 1U) {
        do {
            LapTime *lapTime = &data_0217561c[racerId].lapTimes[lap - 1];

            if (firstLap != 0) {
                leastTime = *lapTime;
                firstLap = 0;
                leastLap = lap;
            } else {
                int isLeast = 0;
                LapTime *copySource;
                u32 lapTotal =
                    lapTime->milliseconds +
                    (lapTime->minutes * 60 + lapTime->seconds) * 1000;
                u32 leastTotal =
                    leastTime.milliseconds +
                    (leastTime.minutes * 60 + leastTime.seconds) * 1000;

                if (lapTotal <= leastTotal) {
                    copySource = lapTime;
                    isLeast = one;
                } else {
                    copySource = &leastTime;
                }

                if (copySource != &leastTime) {
                    Mem_CpuCopy8(copySource, &leastTime, sizeof(leastTime));
                }

                if (isLeast != 0) {
                    leastTime = *lapTime;
                    leastLap = lap;
                }
            }

            lap++;
        } while ((u32)lap <= data_02175620->lapSettings->lapCount);
    }

    *minutes = leastTime.minutes;
    *seconds = leastTime.seconds;
    *milliseconds = leastTime.milliseconds;
    return leastLap;
}
