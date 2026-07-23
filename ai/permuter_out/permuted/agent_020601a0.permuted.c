/* PURPOSE: Gets the kart used by a saved time-trial record.
 * The course id and record-slot index select the record to read.
 * Returns the record's kart id when the read succeeds and the record is valid.
 * Returns -1 when the slot cannot be read or does not contain a valid record.
 */

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
} TimeTrialRecord;

extern int TimeTrialRecord_CopyFrom_from_thumb(
    int courseId, int recordIndex, TimeTrialRecord *record);

int func_020601a0(int courseId, int recordIndex)
{
    TimeTrialRecord record;

    return (TimeTrialRecord_CopyFrom_from_thumb(courseId, recordIndex, &record) &&
            record.isValid)
               ? record.kart
               : -1;
}
