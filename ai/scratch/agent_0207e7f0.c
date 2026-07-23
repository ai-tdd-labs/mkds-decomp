/* func_0207e7f0 (arm) — computes a scaled "reaction" offset vector for an object.
 *
 * arg0 (obj) is a physics/entity struct. obj->f8 (state) holds a VecFx32* (f18,
 * a reference velocity/point) and a fx32 scalar (f1c). obj->f0 points to a body
 * whose position lives at +0x80. obj->f10 is a fixed axis vector.
 *
 * It builds two cross products against a constant up-vector (data_021557c4),
 * derives a signed factor obj->f74 = dot(bodyPos - refPoint, f10 x up) /
 * (state->f1c + 1.0), clamps |f74| to <= 1.0, then writes obj->f44 =
 * refPoint + (f10 x up) * (f74 * state->f1c).
 *
 * NOTE: the clamp reproduces the ROM verbatim — when |f74| > 1.0 it ends up
 * unconditionally set to -0x1000 (looks like an original-game bug where the
 * positive branch is overwritten), so it is written as two sequential
 * statements rather than an if/else. */

typedef int fx32;
typedef long long fx64;
typedef struct { fx32 x, y, z; } VecFx32;

typedef struct State {
    char pad0[0x18];
    VecFx32 *f18;   /* 0x18: reference point/velocity vector */
    fx32 f1c;       /* 0x1c: fx32 scalar */
} State;

typedef struct Body {
    char pad0[0x80];
    VecFx32 f80;    /* 0x80: world position */
} Body;

typedef struct Obj {
    Body *f0;       /* 0x00 */
    int f4;         /* 0x04 */
    State *f8;      /* 0x08 */
    int fc;         /* 0x0c */
    VecFx32 f10;    /* 0x10: axis vector */
    char pad1c[0x44 - 0x1c];
    VecFx32 f44;    /* 0x44: output position */
    char pad50[0x60 - 0x50];
    VecFx32 f60;    /* 0x60: working direction vector */
    char pad6c[0x74 - 0x6c];
    fx32 f74;       /* 0x74: signed factor */
} Obj;

/* out = a x b */
extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
/* out = a - b */
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
/* returns dot(a, b) */
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);
/* fixed-point divide, returns num / den */
extern fx32 FX_Div(fx32 num, fx32 den);
/* absolute value */
extern fx32 AbsValue(fx32 x);
/* out = a + b */
extern void VecFx32_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

extern VecFx32 data_021557c4;   /* constant up-vector */

void func_0207e7f0(Obj *obj) {
    VecFx32 a;  /* refPoint copy */
    VecFx32 b;  /* up-vector copy for 2nd cross */
    VecFx32 c;  /* refPoint copy */
    VecFx32 d;  /* f10 x up */
    VecFx32 e;  /* bodyPos - refPoint */
    VecFx32 f;  /* up-vector */
    VecFx32 g;  /* up-vector */
    /* volatile forces two real reads of the const from a stable scratch reg (ip)
       instead of the compiler CSEing the 2nd read out of g's stack slot */
    volatile VecFx32 *up = &data_021557c4;
    fx32 s;

    a = *obj->f8->f18;
    c = *obj->f8->f18;
    g = *up;
    f = *up;

    Vector3_Cross(&obj->f10, &f, &d);
    VecFx32_Subtract(&obj->f0->f80, &c, &e);

    obj->f74 = FX_Div(VecFx32_CrossProduct_0(&e, &d), obj->f8->f1c + 0x1000);

    if (AbsValue(obj->f74) > 0x1000) {
        if (obj->f74 > 0)
            obj->f74 = 0x1000;
        obj->f74 = -0x1000;
    }

    b = g;
    Vector3_Cross(&obj->f10, &b, &obj->f60);

    s = (fx32)(((fx64)obj->f74 * obj->f8->f1c) >> 12);
    obj->f60.x = (fx32)(((fx64)obj->f60.x * s) >> 12);
    obj->f60.y = (fx32)(((fx64)obj->f60.y * s) >> 12);
    obj->f60.z = (fx32)(((fx64)obj->f60.z * s) >> 12);

    VecFx32_Add(&a, &obj->f60, &obj->f44);
}
