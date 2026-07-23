/*
PURPOSE: Runs one frame of the kart-emblem editor screen, scrolling it and loading the emblem when ready.

Detail: Takes one flag argument (probably "moving backwards/left"); stores it in the
editor state (+0x1e4), ticks two helpers, and if the active slot index (+0x264) is
valid: while a transfer is pending (+0x1d8 or +0x1dc nonzero) it eases a scroll
value (+0x38, via func_02077f0c toward a target with rate 0xeaab), counting frames
(+0x1f0) and cancelling the wait (+0x1dc=0) after 0x3c frames; otherwise it keeps
sliding by 0x64 per frame. The scroll offset (+0x3a) is the (possibly negated) scroll
value depending on the flag. Then it updates the slot's animation and, if both
resource pointers (+0x1e8/+0x1ec) exist and the current element (+0x266) is not
locked, loads the kart emblem image via func_02078e4c. Always ends with func_02077b1c.
Field meanings are guesses; offsets and math are exact.
*/

typedef unsigned short u16;
typedef short s16;

/* scroll sub-block at +0x24 of the state object */
typedef struct {
    char pad0[0x14];
    u16 f14; /* +0x38 abs: scroll value */
    u16 f16; /* +0x3a abs: signed scroll offset actually used */
} CESub;

/* per-slot animation block, stride 0xb8, at +0x58 */
typedef struct {
    char pad0[8];
    void *anim; /* +0x08: animation object for Animation_Update */
    char pad0c[0xac];
} CEAnimSlot;

/* refinement element, stride 0x34, array at +0x1f4 (see func_02078e4c notes) */
typedef struct {
    char pad0[0x2c];
    int lock; /* +0x2c */
    char pad30[4];
} CEElem;

typedef struct {
    char pad00[0x24];
    CESub sub;            /* 0x24 */
    char pad3c[0x1c];     /* 0x3c */
    CEAnimSlot slots[2];  /* 0x58 */
    char pad1c8[0x10];    /* 0x1c8 */
    int f1d8;             /* 0x1d8: transfer/wait flag A */
    int f1dc;             /* 0x1dc: transfer/wait flag B */
    int f1e0;             /* 0x1e0 */
    int f1e4;             /* 0x1e4: the argument is stored here */
    void *f1e8;           /* 0x1e8: resource pointer (emblem image dst?) */
    void *f1ec;           /* 0x1ec: resource pointer (palette dst?) */
    s16 f1f0;             /* 0x1f0: frame counter */
    s16 f1f2;             /* 0x1f2 */
    CEElem elems[2];      /* 0x1f4 */
    char pad25c[8];       /* 0x25c */
    s16 idx;              /* 0x264: active slot index (<0 = none) */
    s16 idx2;             /* 0x266: current element index */
} StructCE;

extern StructCE *data_0217ad08;
extern int data_021656e8;

extern void func_02077b3c(void);
extern void func_020789f4(void);
extern void func_02077f0c(u16 *p, int target, int rate);
extern void Animation_Update(void *anim);
extern void func_02078e4c(void *dst, void *plttDst);
extern void func_02077b1c(void);

void func_02078420(int backwards)
{
    StructCE *b;
    CESub *sub;
    CEAnimSlot *e;
    int idx;

    b = data_0217ad08;
    sub = &b->sub; /* sub-pointer BEFORE the store keeps the base cached */
    b->f1e4 = backwards;
    func_02077b3c();
    func_020789f4();
    b = data_0217ad08; /* reload after the calls */
    idx = b->idx;      /* int local for the bare ldrsh */
    if (idx >= 0) {
        e = &b->slots[idx];
        if (b->f1d8 != 0 || b->f1dc != 0) {
            func_02077f0c(&sub->f14, 0xeaab, data_021656e8);
            b = data_0217ad08; /* reload after the call */
            if (b->f1d8 == 0 && b->f1dc != 0) {
                b->f1f0++;
                b = data_0217ad08; /* ROM reloads before the compare */
                if (b->f1f0 > 0x3c)
                    b->f1dc = 0;
            }
        } else {
            sub->f14 += 0x64;
        }
        /* single shared store: ternary, negate-arm first with explicit u16 cast */
        sub->f16 = (backwards != 0) ? (u16)(0 - sub->f14) : sub->f14;
        Animation_Update(e->anim);
        b = data_0217ad08;
        {
            void *c = b->f1e8;
            if (c != 0) {
                void *d = b->f1ec;
                if (d != 0) {
                    int i2 = b->idx2;
                    if (b->elems[i2].lock == 0)
                        func_02078e4c(c, d);
                }
            }
        }
    }
    func_02077b1c();
}
