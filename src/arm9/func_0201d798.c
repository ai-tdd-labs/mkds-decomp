/* Builds a probably orthonormal third fx16 basis axis from the two axes at
 * arg2 + 0x84, then transforms the fx32 vector in arg1 by that basis.
 * arg0 receives the three fx32 dot-product components.
 */
typedef int fx32;
typedef short fx16;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct VecFx16 {
    fx16 x, y, z;
} VecFx16;

typedef struct BasisOwner {
    unsigned char pad0[0x84];
    VecFx16 axis0;
    VecFx16 axis1;
} BasisOwner;

extern void VecFx16_CrossProduct(const VecFx16 *a, const VecFx16 *b,
                                 VecFx16 *out);
extern void VecFx16_Normalize(const VecFx16 *in, VecFx16 *out);

#define MUL_FX16_FX32(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))

void func_0201d798(VecFx32 *out, const VecFx32 *v, BasisOwner *basis)
{
    VecFx16 axis2;

    VecFx16_CrossProduct(&basis->axis0, &basis->axis1, &axis2);
    VecFx16_Normalize(&axis2, &axis2);

    out->x = MUL_FX16_FX32(v->x, basis->axis0.x)
           + MUL_FX16_FX32(v->y, basis->axis1.x)
           + MUL_FX16_FX32(v->z, axis2.x);
    out->y = MUL_FX16_FX32(v->x, basis->axis0.y)
           + MUL_FX16_FX32(v->y, basis->axis1.y)
           + MUL_FX16_FX32(v->z, axis2.y);
    out->z = MUL_FX16_FX32(v->x, basis->axis0.z)
           + MUL_FX16_FX32(v->y, basis->axis1.z)
           + MUL_FX16_FX32(v->z, axis2.z);
}
