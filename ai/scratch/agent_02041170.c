// PURPOSE: Returns the respawn ID for a course point.
// If the race mode is 2, it advances the course respawn counter cyclically.
// Otherwise it reads the probably per-point respawn ID from the course data.
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int mode;
    int unknown04;
    int unknown08;
    int unknown0c;
    int unknown10;
    int unknown14;
    int unknown18;
    int unknown1c;
    int unknown20;
    int unknown24;
    u16 respawnCount;
} RaceConfig;

typedef struct {
    u8 unknown00[0x22];
    u8 respawnId;
} CoursePoint;

typedef struct {
    u8 unknown00[0x44];
    CoursePoint *points;
} CoursePathState;

extern RaceConfig *gRaceConfig;
extern CoursePathState *data_02175620;
extern long long _s32_div_f(int dividend, int divisor);

u8 GetCourseCpoiRespawnId(int pointId)
{
    u16 respawnId;

    if (gRaceConfig->unknown08 == 2) {
        respawnId = (u16)((unsigned int)_s32_div_f((int)gRaceConfig->respawnCount + 1,
                                                    gRaceConfig->respawnCount) >> 32);
        gRaceConfig->respawnCount = respawnId;
    } else {
        respawnId = data_02175620->points[pointId].respawnId;
    }

    return (u8)respawnId;
}
