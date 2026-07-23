/* func_020ee528 (arm) — refresh a cached transform/frame on an object from its
 * source struct (self->f10) and report whether a derived triple changed.
 *
 * arg0 (self) caches data pulled from src = self->f10:
 *   - a 3x3 matrix (src+0x150 -> self+0x2c)
 *   - two vectors (src+0x98 -> self+0x50, src+0xa4 -> self+0x5c)
 *   - scalars self->f68/f78/f7c (f78 is a rounded fx32 product)
 *   - self->f80 = sign flag of dot(matrix.row2, self->f5c)
 *   - self->f6c = self->f50 - src->f8c
 * It then computes three fx32 products from src (f41c*f428, f420*f42c,
 * f424*f430) and compares them to the cached triple self->f84/88/8c.
 * Returns 0 (and leaves the triple) if all three are unchanged; otherwise
 * stores the new triple and returns 1.  Probably a per-frame dirty check. */

typedef int fx32;
typedef long long fx64;
typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { VecFx32 r0, r1, r2; } Mtx33;   /* 3x3 fx32 matrix, 0x24 bytes */

/* struct pointed to by src->f2cc; only field at +8 is used */
typedef struct P { char pad0[8]; fx32 f8; } P;

typedef struct Src {
    char pad0[0x8c];
    VecFx32 f8c;        /* 0x8c */
    VecFx32 f98;        /* 0x98 */
    VecFx32 fa4;        /* 0xa4 */
    char pad_b0[0xc4 - 0xb0];
    fx32 fc4;           /* 0xc4 */
    char pad_c8[0x150 - 0xc8];
    Mtx33 f150;         /* 0x150 */
    char pad_174[0x2a4 - 0x174];
    fx32 f2a4;          /* 0x2a4 */
    char pad_2a8[0x2bc - 0x2a8];
    fx32 f2bc;          /* 0x2bc */
    char pad_2c0[0x2cc - 0x2c0];
    P *f2cc;            /* 0x2cc */
    char pad_2d0[0x41c - 0x2d0];
    fx32 f41c;          /* 0x41c */
    fx32 f420;
    fx32 f424;
    fx32 f428;
    fx32 f42c;
    fx32 f430;
} Src;

typedef struct Obj {
    char pad0[0x10];
    Src *f10;           /* 0x10: source data */
    char pad14[0x2c - 0x14];
    Mtx33 f2c;          /* 0x2c: cached matrix (row2 at +0x44) */
    VecFx32 f50;        /* 0x50 */
    VecFx32 f5c;        /* 0x5c */
    fx32 f68;           /* 0x68 */
    VecFx32 f6c;        /* 0x6c */
    fx32 f78;           /* 0x78 */
    fx32 f7c;           /* 0x7c */
    int f80;            /* 0x80: sign flag */
    VecFx32 f84;        /* 0x84: dirty-checked triple */
} Obj;

/* returns dot(a, b) */
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);
/* out = a - b */
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int func_020ee528(Obj *self) {
    Src *src = self->f10;
    VecFx32 nv;   /* freshly computed triple, materialized on the stack */
    int unchanged;

    self->f2c = src->f150;
    self->f50 = src->f98;
    self->f5c = src->fa4;
    self->f68 = src->f2a4;
    /* rounded fx32 multiply (+0x800 before >>12) */
    self->f78 = (fx32)(((fx64)src->f2cc->f8 * src->fc4 + 0x800) >> 12);
    self->f7c = src->f2bc;

    /* dot of the matrix's third row with f5c; store its sign */
    self->f80 = VecFx32_CrossProduct_0(&self->f2c.r2, &self->f5c) > 0;

    VecFx32_Subtract(&self->f50, &src->f8c, &self->f6c);

    /* three unrounded fx32 products */
    nv.x = (fx32)(((fx64)src->f41c * src->f428) >> 12);
    nv.y = (fx32)(((fx64)src->f420 * src->f42c) >> 12);
    nv.z = (fx32)(((fx64)src->f424 * src->f430) >> 12);

    /* materialize the equality as an int so mwcc emits moveq/mov + cmp
       (a bool in a register) rather than predicating the return directly */
    if (self->f84.x == nv.x && self->f84.y == nv.y && self->f84.z == nv.z)
        unchanged = 1;
    else
        unchanged = 0;
    if (unchanged)
        goto ret0;

    self->f84 = nv;
    return 1;
ret0:
    return 0;
}
