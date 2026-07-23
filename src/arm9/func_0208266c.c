/* PURPOSE: Aims the camera/racer at a target spot in front of the current player kart on the horizontal (X/Z) plane.
 *
 * Args: arg0 (r5) is some camera/aim object; arg1 (r1) is an "already done" flag.
 *   If arg1 is non-zero the function returns immediately (nothing to do).
 * Behaviour: grabs a global position vector (offset 0x15c of GetGlobalHD4()),
 *   flattens it to the X/Z plane (Y forced to 0). If that horizontal vector is
 *   long enough (squared length >= 0x10) it is normalised. Then it scales the
 *   direction by a fixed factor (data_02165958) and adds it to a base vector
 *   (offset 0x9c) to get a target point. The Y of that point is forced to 0x1f400.
 *   Finally the target is added to a reference position (**obj->0x20, fields +4/+8/+c)
 *   and stored into obj at 0x28/0x2c/0x30.
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
    int f24;
    int f28;
    int f2c;
    int f30;
} Obj;

extern HD *GetGlobalHD4(void);
extern void Vector3_MaybeNormalize(VecFx32 *dst, VecFx32 *src);
extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base, VecFx32 *out);
extern int data_02165958;

void func_0208266c(Obj *obj, int done)
{
    VecFx32 v;
    VecFx32 out;
    HD *hd;

    if (done)
        return;

    hd = GetGlobalHD4();
    v = hd->f15c;                   /* ldm/stm copy of 3 words */
    v.y = 0;
    /* squared length as fx64; y is known 0 -> 0*0 seed. Normalise if long enough. */
    if ((long long)v.x * v.x + (long long)v.y * v.y + (long long)v.z * v.z >= 0x10)
        Vector3_MaybeNormalize(&v, &v);

    VecFx32_AddScale1(data_02165958, &v, &hd->f9c, &out);
    out.y = 0x1f400;

    /* re-deref obj->f20 per field (ROM reloads; store aliasing prevents CSE) */
    obj->f28 = out.x + (*obj->f20)[1];
    obj->f2c = out.y + (*obj->f20)[2];
    obj->f30 = out.z + (*obj->f20)[3];
}
