// PURPOSE: Gets the kart used by a valid saved time-trial record.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct TimeTrialRecord {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u8 recordData[0x14];
    u8 isValid;
    u8 character;
    u8 kart;
    u8 padding_1b;
    u8 unused[8];
} TimeTrialRecord;

extern int TimeTrialRecord_CopyFrom_from_thumb(
    int courseId, int recordIndex, TimeTrialRecord *record);

int func_020601a0(int courseId, int recordIndex)
{
    TimeTrialRecord record;
    int valid;

    valid = TimeTrialRecord_CopyFrom_from_thumb(courseId, recordIndex, &record);
    if (valid != 0)
        if (record.isValid != 0) {
            valid = 1;
            goto status_ready;
        }
    valid = 0;

status_ready:
    return valid != 0 ? record.kart : -1;
}
