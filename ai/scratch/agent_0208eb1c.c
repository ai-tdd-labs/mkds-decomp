// PURPOSE: Starts an award-track effect for one driver.
// The driver index selects the racer whose award path supplies the position.
// The first available group is positioned and moved to the active list.
// This returns null outside award mode or when no group is available.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct RaceConfig {
    int courseId;
    int field_04;
    int raceType;
    int mode;
} RaceConfig;

typedef struct AwardPathData {
    int pathIndex;
    int heightIndex;
    u8 pad_08[0x18];
    u8 *points;
} AwardPathData;

typedef struct DriverEntry {
    u8 pad_000[0x80];
    u8 positionAnchor;
    u8 pad_081[0x50f];
    AwardPathData *awardPath;
} DriverEntry;

typedef struct AwardTrackGroup {
    u8 pad_00[8];
    IntrusiveListWrapper members;
    void *positionAnchor;
    int field_18;
    int halfHeight;
    int driverIndex;
    VecFx32 position;
} AwardTrackGroup;

typedef struct AwardTrackManager {
    IntrusiveListWrapper activeItems;
    IntrusiveListWrapper groups;
    IntrusiveListWrapper freeItems;
} AwardTrackManager;

typedef struct AwardPathColumn {
    int value;
    int unused;
} AwardPathColumn;

extern RaceConfig *gRaceConfig;
extern AwardTrackManager *data_0217b08c;
extern AwardPathColumn data_02166418[];
extern int data_02166480[];
extern AwardPathColumn data_0216641c[];

extern void *IntrusiveListWrapper_GetAtIndex(IntrusiveListWrapper *list,
                                             int index);
extern void IntrusiveListWrapper_RemoveItem(IntrusiveListWrapper *list,
                                            void *item);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                            void *item);
extern DriverEntry *GetDriverEntry(int index);

AwardTrackGroup *func_0208eb1c(int driverIndex)
{
    AwardTrackGroup *group;
    DriverEntry *driver;
    AwardPathData *path;
    VecFx32 position;
    int height;

    if (gRaceConfig->mode != 5) {
        goto notAwardMode;
    }

    group = IntrusiveListWrapper_GetAtIndex(&data_0217b08c->groups, 0);
    if (group != 0) {
        driver = GetDriverEntry(driverIndex);
        path = driver->awardPath;
        position = *(VecFx32 *)(path->points + path->pathIndex * 0xc + 0x44);

        group->positionAnchor = &driver->positionAnchor;
        group->field_18 = 0;
        group->halfHeight = 0x400;
        group->driverIndex = driverIndex;

        height = position.y +
                 (data_02166418[path->pathIndex].value >> 4) -
                 data_02166480[path->heightIndex];
        group->halfHeight = height / 2;
        group->position.x = position.x << 4;
        group->position.y =
            (data_02166480[path->heightIndex] + height / 2) << 4;
        group->position.z =
            data_0216641c[path->pathIndex].value + (position.z << 4);

        IntrusiveListWrapper_RemoveItem(&data_0217b08c->groups, group);
        IntrusiveListWrapper_InsertLast(&data_0217b08c->activeItems, group);
    }

    return group;

notAwardMode:
    return 0;
}
