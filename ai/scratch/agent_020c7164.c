// PURPOSE: Updates the time-trial result flags from the current race times.
// It does nothing outside the time-trial result state or without working data.
// It either checks the save records or compares the current total and best lap
// against the six records held in the working buffer.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct TimeTrialRecord {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u8 unknown_04[0x14];
    u8 valid;
    u8 unknown_19[7];
} TimeTrialRecord;

typedef struct TimeTrialWork {
    u8 unknown_00[8];
    int totalTimeMatches;
    u8 unknown_0c[4];
    int leastLapMatches;
    u16 leastLapId;
    u8 unknown_16[6];
    TimeTrialRecord records[6];
} TimeTrialWork;

typedef struct RaceConfig {
    u8 unknown_00[8];
    int timeTrialResultActive;
    int compareWorkingRecords;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern TimeTrialWork *data_0217b3f4;

extern int GetCurrentPlayerRacerId(void);
extern void GetPlayerTotalTime(int racerId, u8 *minutes, u8 *seconds,
                               u16 *milliseconds);
extern int GetLeastTimeLap(int racerId, u8 *minutes, u8 *seconds,
                           u16 *milliseconds);
extern int CheckHandleSaveTimeTrialRecord2(int saveRecord);
extern int CheckHandleSaveTimeTrialRecord_LeastLap(int saveRecord);

void func_020c7164(void)
{
    u8 totalMinutes;
    u8 totalSeconds;
    u8 lapMinutes;
    u8 lapSeconds;
    u16 totalMilliseconds;
    u16 lapMilliseconds;
    TimeTrialRecord *record;
    int matches;
    int index;
    int totalTime;

    if (gRaceConfig->timeTrialResultActive != 1) {
        return;
    }
    if (data_0217b3f4 == 0) {
        return;
    }

    if (gRaceConfig->compareWorkingRecords == 0) {
        data_0217b3f4->totalTimeMatches =
            CheckHandleSaveTimeTrialRecord2(0);
        data_0217b3f4->leastLapMatches =
            CheckHandleSaveTimeTrialRecord_LeastLap(0);
        return;
    }

    GetPlayerTotalTime(GetCurrentPlayerRacerId(), &totalMinutes,
                       &totalSeconds, &totalMilliseconds);
    totalTime = totalMinutes * 60000 + totalSeconds * 1000 +
                totalMilliseconds;

    matches = 0;
    for (index = 4; index >= 0; index--) {
        record = &data_0217b3f4->records[index];
        if (record->valid != 0 &&
            totalTime == record->minutes * 60000 +
                             record->seconds * 1000 +
                             record->milliseconds) {
            matches = 1;
            break;
        }
    }
    data_0217b3f4->totalTimeMatches = matches;

    record = &data_0217b3f4->records[5];
    data_0217b3f4->leastLapId =
        GetLeastTimeLap(GetCurrentPlayerRacerId(), &lapMinutes, &lapSeconds,
                        &lapMilliseconds);
    data_0217b3f4->leastLapMatches =
        lapMinutes == record->minutes && lapSeconds == record->seconds &&
        lapMilliseconds == record->milliseconds;
}
