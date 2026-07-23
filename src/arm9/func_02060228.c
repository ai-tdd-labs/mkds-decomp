// PURPOSE: Checks whether a time-trial record is valid.
// The two arguments select a record for the save-data reader.
// The copied record layout is partly uncertain; its validity byte is at 0x18.
// Returns one only when copying succeeds and that byte is set.

typedef unsigned char u8;

typedef struct TimeTrialRecord {
    u8 unknown[0x18];
    u8 isValid;
    u8 padding[0xb];
} TimeTrialRecord;

extern int TimeTrialRecord_CopyFrom_from_thumb(
    int courseId, int recordIndex, TimeTrialRecord *record);

int func_02060228(int courseId, int recordIndex)
{
    TimeTrialRecord record;

    if (TimeTrialRecord_CopyFrom_from_thumb(courseId, recordIndex, &record) != 0) {
        if (record.isValid != 0) {
            return 1;
        }
    }
    return 0;
}
