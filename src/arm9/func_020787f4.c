/* PURPOSE: Sets up the menu scene's light and camera from global config values.
 *
 * Arguments: arg0 unused; arg1 (fx32) is added to the camera target's Y.
 * Behaviour: normalizes the configured light direction (if its squared length
 * is big enough), programs light 0's vector and grayscale color, calls a
 * scene helper, then builds a look-at camera matrix from the configured
 * camera position/target (target raised by arg1), storing the derived
 * right/up/target vectors into globals and clearing some flags at
 * data_0217031c+0x7c. Probably a per-frame camera/light refresh.
 */

typedef int fx32;
typedef long long fx64;
typedef unsigned short u16;
typedef signed short s16;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct Struct031C {
    unsigned char pad[0x7c];
    int flags_7c; /* +0x7c: bits 0xE8 cleared here */
} Struct031C;

extern void func_02011034(void);
extern fx64 Multiply64(fx64 a, fx64 b);
extern void Vector3_MaybeNormalize(VecFx32 *a, VecFx32 *b);
extern void func_02010fac(int lightId, s16 x, s16 y, s16 z); /* probably G3_LightVector */
extern void func_02010f98(int lightId, u16 color);           /* probably G3_LightColor */
extern void func_02078934(int arg);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VecFx32_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void G3i_LookAt_(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, int arg3, void *mtx);

extern VecFx32 data_02165708;   /* configured light direction */
extern u16 data_021656d8;       /* light brightness, 5-bit */
extern VecFx32 data_02155188;   /* fixed axis for the cross product */
extern VecFx32 data_021656f0;   /* configured camera target */
extern VecFx32 data_021656fc;   /* configured camera position */
extern VecFx32 data_021704dc;   /* out: camera position copy */
extern VecFx32 data_021704e8;   /* out: camera up/right vector */
extern VecFx32 data_021704f4;   /* out: camera target (with Y offset) */
extern int data_021702e8;       /* out: camera matrix (probably MtxFx43) */
extern Struct031C data_0217031c;

void func_020787f4(int arg0, fx32 arg1)
{
    VecFx32 lightDir; /* sp+0x0c */
    VecFx32 up;       /* sp+0x18 */
    VecFx32 diff;     /* sp+0x24 */
    VecFx32 axis;     /* sp+0x30 */
    VecFx32 target;   /* sp+0x3c */
    fx32 y; /* stack-homed at sp+4 */
    fx32 t, z;
    fx64 sq, xx;
    fx32 x;
    u16 c;

    func_02011034();

    lightDir = data_02165708;
    y = lightDir.y; /* stack-homed at sp+4 */
    /* squared length: zz + (xx + yy), 64-bit */
    z = *(volatile fx32 *)&lightDir.z; /* volatile read pins the load order */
    x = lightDir.x; /* r5 */
    sq = Multiply64(z, z); /* r7:r4 */
    xx = Multiply64(x, x);                   /* lo spilled to sp+8 */
    t = y;                                   /* reload y from its stack home */
    if (sq + (xx + Multiply64(t, t)) >= 16) {
        Vector3_MaybeNormalize(&lightDir, &lightDir);
    }
    func_02010fac(0, (s16)lightDir.x, (s16)lightDir.y, (s16)lightDir.z);

    /* grayscale RGB15 from 5-bit brightness */
    c = data_021656d8;
    func_02010f98(0, (u16)((c << 10) | (c | (c << 5))));

    func_02078934(0);

    axis = data_02155188;
    target = data_021656f0;
    target.y += arg1;
    VecFx32_Subtract(&target, &data_021656fc, &diff);
    VecFx32_CrossProduct(&axis, &diff, &up);

    data_021704dc = data_021656fc;
    data_021704e8 = up;
    data_021704f4 = target;
    G3i_LookAt_(&data_021656fc, &up, &target, 0, &data_021702e8);

    data_0217031c.flags_7c &= ~0xE8;

    func_02011034();
}
