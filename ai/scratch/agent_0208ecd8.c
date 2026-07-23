// PURPOSE: Positions an award-track effect relative to its assigned driver.
// The group selects a driver and supplies offsets along the driver's three axes.
// The transformed position is stored in the effect at one-sixteenth precision.
// The group's half-height is copied to the effect and its state field is cleared.

typedef int fx32;
typedef long long fx64;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct DriverEntry {
    u8 pad_000[0x80];
    VecFx32 position;
    u8 pad_08c[0x120 - 0x8c];
    VecFx32 axis0;
    VecFx32 axis1;
    VecFx32 axis2;
} DriverEntry;

typedef struct AwardTrackGroup {
    u8 pad_00[0x1c];
    int halfHeight;
    int driverIndex;
    VecFx32 localOffset;
} AwardTrackGroup;

typedef struct AwardTrackInstance {
    u8 pad_00[8];
    int halfHeight;
    u16 state;
    u16 pad_0e;
    VecFx32 position;
} AwardTrackInstance;

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (fx32)(b)) >> 12))

extern DriverEntry *GetDriverEntry(int index);
extern void VecFx32_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);

void func_0208ecd8(AwardTrackInstance *instance, AwardTrackGroup *group)
{
    VecFx32 position;
    VecFx32 axisOffset0;
    VecFx32 axisOffset1;
    VecFx32 axisOffset2;
    DriverEntry *driver;

    driver = GetDriverEntry(group->driverIndex);
    position = driver->position;

    {
        fx32 x = group->localOffset.x;
        axisOffset0.x = FX_MUL(driver->axis0.x, x);
        axisOffset0.y = FX_MUL(driver->axis0.y, x);
        axisOffset0.z = FX_MUL(driver->axis0.z, x);
    }

    {
        fx32 y = group->localOffset.y;
        axisOffset1.x = FX_MUL(driver->axis1.x, y);
        axisOffset1.y = FX_MUL(driver->axis1.y, y);
        axisOffset1.z = FX_MUL(driver->axis1.z, y);
    }

    {
        fx32 z = group->localOffset.z;
        axisOffset2.x = FX_MUL(driver->axis2.x, z);
        axisOffset2.y = FX_MUL(driver->axis2.y, z);
        axisOffset2.z = FX_MUL(driver->axis2.z, z);
    }

    VecFx32_Add(&position, &axisOffset0, &position);
    VecFx32_Add(&position, &axisOffset1, &position);
    VecFx32_Add(&position, &axisOffset2, &position);

    instance->halfHeight = group->halfHeight;
    instance->state = 0;
    instance->position.x = position.x >> 4;
    instance->position.y = position.y >> 4;
    instance->position.z = position.z >> 4;
}
