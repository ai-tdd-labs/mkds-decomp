// PURPOSE: Copies a saved time-trial record into an output record.
// The internal course ID selects a saved record, and the bank selects its group.
// It returns whether the course ID was valid; an invalid result clears the output flag.
// The record layout and the save-data field names are inferred from nearby code.

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
extern void TimeTrialRecord_CopyFromImpl_from_thumb(
    const TimeTrialRecord *source, TimeTrialRecord *destination);

int TimeTrialRecord_CopyFrom_from_thumb(int internalId, int recordBank,
                                        TimeTrialRecord *destination)
{
    int result;
    int courseId = GetCourseIdFromInternalId(internalId);

    result = 1;
    if (courseId != -1) {
        TimeTrialRecord_CopyFromImpl_from_thumb(
            &data_0217aa08->timeTrials->records[recordBank][courseId], destination);
    } else {
        result = 0;
    }

    if (result == 0) {
        destination->data[0x18] = 0;
    }

    return result;
}
