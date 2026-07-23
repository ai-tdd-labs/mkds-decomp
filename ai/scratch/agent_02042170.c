// PURPOSE: Loads course camera records and remembers cameras with special roles.
// Advances the CAME section cursor, stores its records globally, and scans them.
// The cached pointers probably select race, replay, and course-intro cameras.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct NkmCameraRecord {
    u8 pad_00[0x3e];
    u16 type;
    u8 pad_40[0x0a];
    u8 role;
    u8 pad_4b;
} NkmCameraRecord;

typedef struct CoursePathState {
    u8 pad_000[0x7c];
    NkmCameraRecord *cameraRecords;
    u16 cameraRecordCount;
    u8 pad_082[0x42];
    NkmCameraRecord *role1Camera;
    NkmCameraRecord *role2Camera;
    NkmCameraRecord *type6Camera;
    NkmCameraRecord *type7Camera;
    NkmCameraRecord *type8Camera;
} CoursePathState;

typedef struct RaceConfig {
    u8 pad_00[8];
    int mode;
} RaceConfig;

extern CoursePathState *data_02175620;
extern RaceConfig *gRaceConfig;
extern u16 NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_CAME_from_thumb(void *sectionCursor)
{
    u16 i;

    data_02175620->cameraRecordCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->cameraRecordCount == 0) {
        data_02175620->cameraRecords = 0;
        return 1;
    }

    data_02175620->cameraRecords = sectionCursor;
    data_02175620->role1Camera = 0;
    data_02175620->role2Camera = 0;
    data_02175620->type6Camera = 0;
    data_02175620->type7Camera = 0;

    for (i = 0; i < data_02175620->cameraRecordCount; i++) {
        NkmCameraRecord *camera = &data_02175620->cameraRecords[i];

        if (data_02175620->role1Camera == 0 && camera->role == 1) {
            data_02175620->role1Camera = camera;
        }
        if (data_02175620->role2Camera == 0 && camera->role == 2) {
            data_02175620->role2Camera = camera;
        }
        if (data_02175620->type6Camera == 0 && camera->type == 6) {
            data_02175620->type6Camera = camera;
        }
        if (gRaceConfig->mode == 2 && data_02175620->type7Camera == 0 &&
            camera->type == 7) {
            data_02175620->type7Camera = camera;
        }
        if (gRaceConfig->mode == 4 && data_02175620->type8Camera == 0 &&
            camera->type == 8) {
            data_02175620->type8Camera = camera;
        }
    }

    return 1;
}
