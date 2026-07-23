// PURPOSE: Saves a faster least-lap time-trial record.
// The argument controls whether the improved lap is copied into the working
// record and persistent save data. The function returns zero when the current
// saved lap is already as fast, and one otherwise.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TimeTrialRecord {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u16 racerName[10];
    u8 isValid;
    u8 characterId;
    u8 kartId;
    u8 unknown_1b;
} TimeTrialRecord;

typedef struct TimeTrialRecordSet {
    u8 unknown_00[0xa0];
    TimeTrialRecord leastLap;
} TimeTrialRecordSet;

typedef struct TimeTrialWork {
    u8 unknown_00[0x14];
    u16 leastLapId;
    u8 unknown_16[6];
    TimeTrialRecordSet records;
} TimeTrialWork;

typedef struct RacerSlot {
    u8 raw[0x30];
} RacerSlot;

typedef struct RacerRecord {
    u8 unknown_00[0x68];
    u32 characterId;
    u32 kartId;
    u8 unknown_70[0x18];
    u16 *name;
} RacerRecord;

extern TimeTrialWork *data_0217b3f4;
extern RacerSlot *gRaceConfig;

extern int GetCurrentPlayerRacerId(void);
extern int GetLeastTimeLap(int racerId, u8 *minutes, u8 *seconds,
                           u16 *milliseconds);
extern void CopyMemory16(const void *source, void *destination, u32 size);
extern void TimeTrialCopyToSaveData_from_thumb(
    int internalId, int recordBank, const TimeTrialRecord *source);

int CheckHandleSaveTimeTrialRecord_LeastLap(int saveRecord)
{
    u8 minutes;
    u8 seconds;
    u16 milliseconds;
    TimeTrialRecordSet *records;
    TimeTrialRecord *record;

    record = &data_0217b3f4->records.leastLap;
    data_0217b3f4->leastLapId =
        GetLeastTimeLap(GetCurrentPlayerRacerId(), &minutes, &seconds,
                        &milliseconds);

    if (record->isValid != 0) {
        if (seconds * 1000 + minutes * 60000 + milliseconds >=
            record->seconds * 1000 + record->minutes * 60000 +
                record->milliseconds) {
            return 0;
        }
    }

    if (saveRecord != 0) {
        u16 savedMilliseconds = milliseconds;
        u8 savedSeconds = seconds;
        u8 savedMinutes = minutes;

        records = &data_0217b3f4->records;
        record = &records->leastLap;
        record->minutes = savedMinutes;
        record->seconds = savedSeconds;
        records->leastLap.milliseconds = savedMilliseconds;

        CopyMemory16(
            ((RacerRecord *)&gRaceConfig[GetCurrentPlayerRacerId()])->name,
            record->racerName, sizeof(record->racerName));
        record->isValid = 1;
        record->characterId =
            ((RacerRecord *)&gRaceConfig[GetCurrentPlayerRacerId()])
                ->characterId;
        record->kartId =
            ((RacerRecord *)&gRaceConfig[GetCurrentPlayerRacerId()])->kartId;

        TimeTrialCopyToSaveData_from_thumb(*(int *)gRaceConfig, 5, record);
    }

    return 1;
}
