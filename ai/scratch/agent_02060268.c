// PURPOSE: Checks whether all time-trial record slots are empty.
// The argument is an internal course ID, which is validated before use.
// A personal ghost must exist before the six saved record slots are checked.
// The byte at offset 0x18 probably marks a copied record as valid.
// Returns zero when a valid saved record is found, otherwise one.

#pragma optimize_for_size off

typedef unsigned char u8;

typedef struct TimeTrialRecord {
    u8 unknown[0x18];
    u8 isValid;
    u8 padding[0xb];
} TimeTrialRecord;

extern int GetCourseIdFromInternalId(int internalId);
extern int MaybeHasPersonalGhostForCourse_from_thumb(u8 courseId);
extern int TimeTrialRecord_CopyFrom_from_thumb(
    int internalId, int recordIndex, TimeTrialRecord *record);

int CourseTimeTrialRecordsEmpty(int internalId)
{
    TimeTrialRecord record;
    u8 recordIndex;
    int result = 1;
    register int zero = 0;
    register int one = 1;
    int courseId;

    courseId = GetCourseIdFromInternalId(internalId);
    if (courseId == -1) {
        return result;
    }

    if (MaybeHasPersonalGhostForCourse_from_thumb((u8)courseId) == 0) {
        return result;
    }

    for (recordIndex = 0; recordIndex < 6; recordIndex++) {
        register int found =
            TimeTrialRecord_CopyFrom_from_thumb(internalId, recordIndex, &record) != 0;

        if (found != 0) {
            found = record.isValid != 0;
        }
        if (found != 0) {
            result = zero;
            break;
        }
    }

    return result;
}
