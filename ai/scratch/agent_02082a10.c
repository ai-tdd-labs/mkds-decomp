/* PURPOSE: Places an object's target point a fixed distance ahead of the player kart on the flat (X/Z) ground.
 *
 * Args: arg0 (r5) is some aim/marker object; arg1 (r1) is an "already done" flag.
 *   If arg1 is non-zero the function returns immediately (nothing to do).
 * Behaviour: reads a global direction vector (offset 0x15c of GetGlobalHD5()),
 *   flattens it onto the X/Z plane (Y forced to 0). If that horizontal vector is
 *   long enough (3D squared length >= 0x10) it is normalised. Then it scales the
 *   direction by a fixed factor (0x5800) and adds it to a base position (offset 0x9c)
 *   to get a target point; the target's Y is forced to 0x1f400. Finally the target
 *   is added to a reference position (**obj->0x20, fields +4/+8/+c) and written into
 *   obj at 0x28/0x2c/0x30.
 */

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char pad9c[0x9c];
    VecFx32 f9c;                    /* base position vector */
    char pad2[0x15c - 0x9c - 12];
    VecFx32 f15c;                   /* direction vector (flattened, normalised) */
} HD;

typedef struct {
    char pad0[0x20];
    int **f20;                      /* pointer to pointer to a reference position */
    int f24, f28, f2c, f30;
} Obj;

extern HD *GetGlobalHD5(void);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base, VecFx32 *out);

void func_02082a10(Obj *obj, int done)
{
    VecFx32 v;
    VecFx32 out;
    HD *hd;

    if (done)
        return;

    hd = GetGlobalHD5();
    v = hd->f15c;                   /* ldm/stm copy of 3 words */
    v.y = 0;                        /* zero kept in lr, reused as y*y seed */
    /* full 3D squared length (y==0); normalise only if long enough.
       Including y*y makes mwcc seed the fx64 accumulator with 0*0. */
    if ((long long)v.x * v.x + (long long)v.y * v.y +
        (long long)v.z * v.z >= 0x10)
        Vector3_MaybeNormalize(&v, &v);

    VecFx32_AddScale1(0x5800, &v, &hd->f9c, &out);
    out.y = 0x1f400;

    /* reload obj->f20 and deref per store (ROM repeats ldr [r5,#0x20]; ldr [r0]) */
    obj->f28 = out.x + (*obj->f20)[1];
    obj->f2c = out.y + (*obj->f20)[2];
    obj->f30 = out.z + (*obj->f20)[3];
}
