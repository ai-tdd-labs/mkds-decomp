// Transforms a local-space vector into world space using an object's basis.
// Args: dst (fx32 vec3 out), v (fx32 vec3 in), obj with two VecFx16 basis
// vectors at +0x84 (probably "right"/tangent) and +0x8a (probably "up").
// The third basis vector is normalize(cross(a, b)); each output component is
// FX_Mul(v->z, n.c) + (FX_Mul(v->x, a.c) + FX_Mul(v->y, b.c)).

typedef signed short fx16;
typedef int fx32;
typedef long long fx64;

typedef struct {
    fx16 x, y, z;
} VecFx16;

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct {
    unsigned char pad_00[0x84];
    VecFx16 a; // 0x84: first basis vector (fx16)
    VecFx16 b; // 0x8a: second basis vector (fx16)
} UnkObj;

extern void VecFx16_CrossProduct(const VecFx16 *a, const VecFx16 *b, VecFx16 *dst);
extern void VecFx16_Normalize(const VecFx16 *src, VecFx16 *dst);

// fx32 * fx16 multiply with rounding, same as FX_Mul
#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))

void func_0201d798(VecFx32 *dst, const VecFx32 *v, UnkObj *obj)
{
    VecFx16 n;

    VecFx16_CrossProduct(&obj->a, &obj->b, &n);
    VecFx16_Normalize(&n, &n);

    // parenthesization matches ROM add tree: cross-term + (a-term + b-term)
    dst->x = FX_MUL(v->z, n.x) + (FX_MUL(v->x, obj->a.x) + FX_MUL(v->y, obj->b.x));
    dst->y = FX_MUL(v->z, n.y) + (FX_MUL(v->x, obj->a.y) + FX_MUL(v->y, obj->b.y));
    dst->z = FX_MUL(v->z, n.z) + (FX_MUL(v->x, obj->a.z) + FX_MUL(v->y, obj->b.z));
}
