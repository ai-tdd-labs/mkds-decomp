// PURPOSE: Loads the selected personal ghost when it is available.
// Converts the internal course ID, clears the request flag for an invalid or
// missing ghost, and otherwise starts the personal-ghost save-data read.
// The request context and flag layout are inferred from nearby save routines.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct PersonalGhostRequest {
    u8 unknown_00[8];
    u32 flags;
} PersonalGhostRequest;

typedef struct SaveDataContext {
    u8 unknown_00[0x14];
    PersonalGhostRequest *personalGhostRequest;
} SaveDataContext;

extern SaveDataContext *data_0217aa08;

extern int GetCourseIdFromInternalId(int internalId);
extern int MaybeHasPersonalGhostForCourse_from_thumb(u8 courseId);
extern void ReadSaveDataSection_PersonalGhost_from_thumb(
    u32 ghostSlot, u32 requestContext);

void func_02056700(int internalId)
{
    int unavailable = 0;
    int courseId = GetCourseIdFromInternalId(internalId);
    PersonalGhostRequest *request = data_0217aa08->personalGhostRequest;

    if (courseId == -1) {
        unavailable = 1;
    } else if (MaybeHasPersonalGhostForCourse_from_thumb((u8)courseId) == 0) {
        unavailable = 1;
    }

    if (unavailable != 0) {
        request->flags &= ~1;
    } else {
        ReadSaveDataSection_PersonalGhost_from_thumb((u8)courseId, (u32)request);
    }
}
