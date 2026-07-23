// PURPOSE: Generates a random normalized flat direction vector.
// The output receives two fixed-point components from the shared random seed.
// Its third component is zero before the vector is normalized in place.

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

extern int data_02173274;
extern void VecFx32_Normalize(const VecFx32 *src, VecFx32 *dst);

void func_0201e4e4(VecFx32 *out)
{
    data_02173274 = data_02173274 * 0x5eedf715 + 0x1b0cb173;
    out->x = data_02173274 >> 8;

    data_02173274 = data_02173274 * 0x5eedf715 + 0x1b0cb173;
    out->y = data_02173274 >> 8;
    out->z = 0;

    VecFx32_Normalize(out, out);
}
