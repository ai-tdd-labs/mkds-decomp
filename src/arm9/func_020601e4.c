// PURPOSE: Gets the character used by a valid time-trial record.
// The course id and record-slot index select the saved record to inspect.
// Byte 0x18 is probably its validity flag, and byte 0x19 is the character id.
// Returns one for a valid record, otherwise probably its character or -1.

#pragma optimize_for_size on

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
    u8 padding_1b[5];
} TimeTrialRecord;

extern int TimeTrialRecord_CopyFrom_from_thumb(
    int courseId, int recordIndex, TimeTrialRecord *record);

int func_020601e4(int courseId, int recordIndex)
{
    TimeTrialRecord record;

    int result = TimeTrialRecord_CopyFrom_from_thumb(courseId, recordIndex, &record);

    if (result == 0)
        goto fallback;
    result = record.isValid;
    if (result != 0) {
        result = 1;
        goto done;
    }

fallback:
    result = 0;
done:
    return result ? record.character : -1;
}
