// PURPOSE: Checks whether a driver is inside any course volume in a selected group.
// The first argument selects the driver whose position is tested.
// The second argument selects a linked list of course volumes.
// It returns one when any regular or probably rounded volume contains the driver.

typedef unsigned char u8;
typedef unsigned short u16;
typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct OrientedVolume {
    VecFx32 origin;
    fx32 extent0;
    fx32 extent1;
    fx32 extent2;
    VecFx32 axis0;
    VecFx32 axis1;
    VecFx32 axis2;
    u8 pad3c[6];
    u8 mode;
} OrientedVolume;

typedef struct VolumeNode {
    OrientedVolume *volume;
    struct VolumeNode *next;
} VolumeNode;

typedef struct CoursePathState {
    u8 pad000[0xd8];
    VolumeNode *volumeLists[1];
} CoursePathState;

extern CoursePathState *data_02175620;
extern void GetDriverMaybeSfxPosition(VecFx32 *position, u16 driverIndex);
extern int func_02041a70(const VecFx32 *point,
                         const OrientedVolume *volume);
extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))

int func_02040de0(u16 driverIndex, int groupIndex)
{
    VecFx32 position;
    VecFx32 offset;
    VolumeNode *node = data_02175620->volumeLists[groupIndex];
    int result = 0;
    int inside;

    GetDriverMaybeSfxPosition(&position, driverIndex);
    inside = 0;

    while (result == 0 && node != 0) {
        OrientedVolume *volume = node->volume;

        switch (volume->mode) {
        case 0:
            inside = func_02041a70(&position, volume);
            break;

        case 1: {
            fx32 radius;
            fx32 projection2;
            fx32 projection0;

            VecFx32_Subtract(&position, &volume->origin, &offset);

            if (Vector3_DotProduct(&offset, &volume->axis1) <=
                (fx32)(((fx64)volume->extent1 * 0x32000 + 0x800) >> 12)) {
                projection0 =
                    Vector3_DotProduct(&offset, &volume->axis0) >> 4;
                projection2 =
                    Vector3_DotProduct(&offset, &volume->axis2) >> 4;
                radius =
                    (fx32)(((fx64)volume->extent0 * 0x32000 + 0x800) >>
                           12) >>
                    4;

                if (FX_MUL(radius, radius) >=
                    FX_MUL(projection0, projection0) +
                        FX_MUL(projection2, projection2)) {
                    inside = 1;
                }
            }
            break;
        }
        }

        node = node->next;
        if (inside != 0)
            result = 1;
    }

    return result;
}
