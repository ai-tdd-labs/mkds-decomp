/* PURPOSE: Sets up the 3D camera frustum for a screen, optionally mirrored.
 *
 * Computes a fixed-point aspect value from FX_Div(0x579, 0xf09), derives the
 * frustum top/bottom from it, and the left/right edges via a 64-bit multiply
 * with 0x1555. If the argument (probably a mirror/flip flag) is nonzero the
 * left/right edges are swapped (negated). Then it records a graphics command
 * (id 0x15), loads the frustum with near=0x200 far=0x64000 scale=0x1000 into
 * the projection matrix at data_021702a4, clears bits 0x50 in a state word of
 * data_0217031c, and calls func_02011034 (probably to apply the matrices).
 */

typedef int fx32;
typedef long long fx64;
typedef unsigned int u32;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx64 Multiply64(fx64 a, fx64 b);
extern void func_01ff9048(u32 id, void *ptr, u32 count);
extern void G3i_FrustumW_(fx32 top, fx32 bottom, fx32 left, fx32 right,
                          fx32 near, fx32 far, fx32 scaleW, int flag,
                          void *mtx);
extern void func_02011034(void);

typedef struct {
    unsigned char pad_00[0x7c];
    int flags_7c; /* bits 0x50 cleared here */
} Struct0217031c;

extern char data_021702a4[]; /* projection matrix (bss) */
extern Struct0217031c data_0217031c;

void func_02078934(int flip)
{
    fx32 q;
    fx32 left;
    fx32 bottom;
    fx32 top;
    fx32 right;

    q = FX_Div(0x579, 0xf09);
    /* 64-bit multiply by 0x200 folds to a shift pair */
    top = (fx32)(((fx64)q * 0x200) >> 12);
    bottom = -top;
    left = (fx32)(Multiply64(bottom, 0x1555) >> 12);
    right = -left;
    if (flip != 0) {
        right = -right;
        left = -left;
    }
    func_01ff9048(0x15, 0, 0);
    G3i_FrustumW_(top, bottom, left, right, 0x200, 0x64000, 0x1000, 0,
                  data_021702a4);
    data_0217031c.flags_7c &= ~0x50;
    func_02011034();
}
