// PURPOSE: Formats a racer name for the time-trial records screen.
// Record zero uses the current racer; later indices use saved records.
// The output is cleared before a valid name is copied.
// The final argument selects fixed or font-clamped length.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TimeTrialRecord {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u16 racerName[10];
    u8 isValid;
    u8 character;
    u8 kart;
    u8 unknown_1b;
} TimeTrialRecord;

typedef struct RaceRacerRecord {
    u32 type;
    u8 unknown_04[0x14];
    u16 *name;
    u8 unknown_1c[0x14];
} RaceRacerRecord;

typedef struct RaceConfig {
    int internalCourseId;
    u8 unknown_004[0x6c];
    RaceRacerRecord racers[8];
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern int TimeTrialRecord_CopyFrom_from_thumb(
    int internalCourseId, int recordIndex, TimeTrialRecord *record);
extern int GetClampedString10LengthForFontIndex0_from_thumb(
    u16 *string, u16 *scratch);
extern void CopyString16(u16 *destination, u16 *source, int count);

void FormatTimeTrialRecordRacerNameString(int recordIndex, u16 *destination,
                                          int useFixedLength)
{
    u16 scratch[10];
    TimeTrialRecord record;
    int count = 0;
    u16 *name = 0;
    u16 i;
    int valid = 0;

    for (i = 0; i < 11; i++) {
        destination[i] = 0;
    }

    if (recordIndex == 0) {
        u32 type = gRaceConfig->racers[recordIndex].type;

        if (type <= 3 && ((1u << type) & 0xd) != 0) {
            valid = 1;
        }

        if (valid != 0) {
            name = gRaceConfig->racers[recordIndex].name;
            if (name == 0) {
                return;
            }

            if (useFixedLength != 0) {
                count = 10;
            } else {
                count = GetClampedString10LengthForFontIndex0_from_thumb(
                    name, scratch);
            }
        }
    } else {
        if (TimeTrialRecord_CopyFrom_from_thumb(
                gRaceConfig->internalCourseId, recordIndex - 1, &record) != 0) {
            name = record.racerName;
            if (useFixedLength != 0) {
                count = 10;
            } else {
                count = GetClampedString10LengthForFontIndex0_from_thumb(
                    name, scratch);
            }
        }
    }

    if (name == 0) {
        return;
    }
    CopyString16(destination, name, count);
}
