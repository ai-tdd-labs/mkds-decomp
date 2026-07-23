// PURPOSE: Initializes a driver's race-result record for the current race.
// result receives default counters, checkpoint limits, and formatted race times.
// racerIndex selects the driver and is packed into the result flags.
// Some checkpoint-field meanings are still uncertain.

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NkmCpatRecord {
    u16 pointStart;
    u16 pointCount;
    u8 nextGroups[3];
    u8 previousGroups[3];
    u8 sectionOrderA;
    u8 sectionOrderB;
} NkmCpatRecord;

typedef struct CoursePathState {
    u8 padding_000[0x44];
    void *cpoiEntries;
    u8 padding_048[0x4c - 0x48];
    NkmCpatRecord *cpatEntries;
} CoursePathState;

typedef struct RaceState {
    u32 elapsedTime;
    u8 padding_004[0x98 - 0x04];
    u16 racerCount;
} RaceState;

typedef struct RaceConfig {
    u8 padding_000[0x62];
    s8 selectedRacer;
} RaceConfig;

typedef struct DriverRaceResult {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u8 splitTimes[5][4];
    u8 totalTime[4];
    u32 field_24;
    u32 field_28;
    u32 field_2c;
    u16 flags_30;
    u16 lastCoursePoint;
    u16 lastRacer_34;
    u16 lastRacer_36;
    u16 previousPath;
    u16 field_3a;
    u16 settings_3c;
    u16 field_3e;
    u32 field_40;
    u32 field_44;
    u32 field_48;
} DriverRaceResult;

extern CoursePathState *data_02175620;
extern RaceState *data_0217561c;
extern RaceConfig *gRaceConfig;

extern void MaybeConvertElapsedTime(u8 *part2, u8 *part3, u8 *part0,
                                    int part1, u32 elapsedTime);

void StructRC_SomeFn_2(DriverRaceResult *result, int racerIndex)
{
    int i;

    if (data_02175620->cpoiEntries != 0) {
        result->previousPath =
            data_02175620->cpatEntries->previousGroups[0];
        result->lastCoursePoint =
            data_02175620->cpatEntries[result->previousPath].pointStart +
            data_02175620->cpatEntries[result->previousPath].pointCount - 1;
    } else {
        result->previousPath = 0;
        result->lastCoursePoint = 0;
    }

    result->field_04 = 0;
    result->field_08 = 0;
    result->field_2c = 0;
    result->field_3a = 1;
    result->field_24 = 0;
    result->field_00 = 0;
    result->flags_30 = 0;
    result->lastRacer_34 = data_0217561c->racerCount - 1;
    result->lastRacer_36 = data_0217561c->racerCount - 1;

    result->settings_3c =
        (result->settings_3c & ~0xf0) |
        ((((u16)racerIndex) & 0xf) << 4);

    result->field_44 = 0;
    result->field_48 = 0;
    result->field_3e = 0;
    result->field_28 = 0;
    result->field_40 = 0;
    result->settings_3c &= ~0x300;

    for (i = 0; i < 5; i++) {
        u8 *time = result->splitTimes[i];

        MaybeConvertElapsedTime(time + 2, time + 3, time, 0,
                                data_0217561c->elapsedTime);
    }

    MaybeConvertElapsedTime(result->totalTime + 2, result->totalTime + 3,
                            result->totalTime, 0,
                            data_0217561c->elapsedTime);

    if (racerIndex == gRaceConfig->selectedRacer) {
        result->flags_30 |= 1;
    }

    result->settings_3c =
        (result->settings_3c & ~0xf) |
        (((u16)(racerIndex + 1)) & 0xf);
}
