// PURPOSE: Builds the object's camera view matrix.
// The object supplies camera position, target, up-vector, and matrix storage.
// A vertical offset probably raises or lowers the camera before conversion.

typedef int fx32;
typedef long long fx64;
typedef unsigned int u32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct StructHD {
    VecFx32 up;
    unsigned char pad_00c[0x18 - 0x0c];
    VecFx32 target;
    VecFx32 position;
    unsigned char matrix[0x15c - 0x30];
    VecFx32 direction;
    unsigned char pad_168[0x178 - 0x168];
    fx32 verticalOffset;
} StructHD;

extern VecFx32 data_02154fc4;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void G3i_LookAt_(const VecFx32 *position, const VecFx32 *up,
                        const VecFx32 *target, int mode, void *matrix);

void StructHD_SomeFn_10(StructHD *obj)
{
    VecFx32 cross;
    VecFx32 direction;
    VecFx32 reference;
    VecFx32 position;
    VecFx32 target;

    reference = data_02154fc4;
    VecFx32_Subtract(&obj->target, &obj->position, &direction);

    if ((fx64)direction.x * direction.x +
            (fx64)direction.y * direction.y +
            (fx64)direction.z * direction.z >=
        0x10) {
        Vector3_MaybeNormalize(&direction, &direction);
    }

    obj->direction = direction;
    Vector3_Cross(&reference, &direction, &cross);
    Vector3_Cross(&direction, &cross, &obj->up);

    if (obj->up.x == 0 && obj->up.y == 0 && obj->up.z == 0) {
        obj->up.x = 0x1000;
        obj->up.y = 0x1000;
        obj->up.z = 0x1000;

        if ((fx64)obj->up.x * obj->up.x +
                (fx64)obj->up.y * obj->up.y +
                (fx64)obj->up.z * obj->up.z >=
            0x10) {
            Vector3_MaybeNormalize(&obj->up, &obj->up);
        }
    }

    *(volatile u32 *)0x04000440 = 2;

    position.x = obj->position.x >> 4;
    position.y = (obj->position.y + obj->verticalOffset) >> 4;
    position.z = obj->position.z >> 4;

    target.x = obj->target.x >> 4;
    target.y = obj->target.y >> 4;
    target.z = obj->target.z >> 4;

    G3i_LookAt_(&position, &obj->up, &target, 1, obj->matrix);
}
