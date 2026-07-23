/* PURPOSE: Copies a time-trial record into save data.
 * The first argument is converted from an internal course ID to a save-course
 * index. The second argument probably selects a time-trial record bank, and
 * the third points to the record to copy. Invalid course IDs are ignored.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TimeTrialRecord {
    u8 data[0x1c];
} TimeTrialRecord;

typedef struct TimeTrialSaveData {
    u32 header;
    TimeTrialRecord records[4][32];
} TimeTrialSaveData;

typedef struct SaveDataContext {
    u8 unknown_00[0xc];
    TimeTrialSaveData *timeTrials;
} SaveDataContext;

extern SaveDataContext *data_0217aa08;

extern int GetCourseIdFromInternalId(int internalId);
extern void TimeTrialRecordCopyTo_from_thumb(TimeTrialRecord *destination,
                                             const TimeTrialRecord *source);

void TimeTrialCopyToSaveData_from_thumb(int internalId, int recordBank,
                                        const TimeTrialRecord *source)
{
    int courseId = GetCourseIdFromInternalId(internalId);

    if (courseId == -1) {
        return;
    }

    TimeTrialRecordCopyTo_from_thumb(
        &data_0217aa08->timeTrials->records[recordBank][courseId], source);
}
