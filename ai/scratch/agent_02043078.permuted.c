// PURPOSE: Calculates a course path's distance including the average distance of its branches.

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct NkmPointRecord {
    u8 pad_00[0x18];
    int distance;
    u8 pad_1c[8];
} NkmPointRecord;

typedef struct NkmPathRecord {
    u16 firstPointIndex;
    u16 pointCount;
    s8 nextPathIndices[3];
    s8 pad_07;
    u8 pad_08[4];
} NkmPathRecord;

typedef struct CoursePathState {
    u8 pad_000[0x44];
    NkmPointRecord *points;
    u8 pad_048[4];
    NkmPathRecord *paths;
} CoursePathState;

extern CoursePathState *data_02175620;
extern int _s32_div_f(int numerator, int denominator);

int ComputeTotalDistanceRecursively_from_thumb(int pathIndex)
{
    int branchDistance;
    NkmPathRecord *path;
    int distance;
    u16 branchCount;
    u16 pointIndex;
    u16 linkIndex;
    u16 pointOffset;

    path = &data_02175620->paths[pathIndex];
    branchDistance = 0;
    branchCount = 0;
    distance = 0;

    for (pointIndex = 0; pointIndex < path->pointCount; pointIndex++) {
        pointOffset = (u16)(path->firstPointIndex + pointIndex);
        distance += data_02175620->points[pointOffset].distance;
    }

    for (linkIndex = 0; linkIndex < 3; linkIndex++) {
        int linkedPath = path->nextPathIndices[linkIndex];

        if (linkedPath != -1 && linkedPath != 0) {
            branchDistance +=
                ComputeTotalDistanceRecursively_from_thumb((u16)linkedPath);
            branchCount++;
        }
    }

    if (branchCount != 0) {
        distance += _s32_div_f(branchDistance, branchCount);
    }

    return distance;
}
