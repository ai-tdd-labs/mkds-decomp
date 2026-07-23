/* PURPOSE: Animates the selected kart and loads its emblem into video memory.
 *
 * No arguments. Every frame on the kart-select screen this advances the
 * animation of the currently selected kart's model (subs[f264] field +0x08)
 * and, when the current elems[f266] entry is not locked (+0x2c == 0), calls
 * func_02078e4c to queue the kart emblem image and palette VRAM transfers.
 * The two 0x021a2xxx library calls (module:none, no symbols) probably return
 * the OBJ character and palette destination pointers for the emblem.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct StructCESub {
    u8 pad_00[0x08];
    void *f08;            /* 0x08: animation object of this kart model */
    u8 pad_0c[0x08];
    void *f14;            /* 0x14: resource holder (file at +4) */
    u8 pad_18[0xa0];
} StructCESub;            /* size 0xb8 */

typedef struct CEElem {
    u8 pad_00[0x2c];
    int f2c;              /* 0x2c: lock/busy word */
    u8 pad_30[4];
} CEElem;                 /* size 0x34 */

typedef struct StructCE {
    u8 pad_00[0x58];
    StructCESub subs[2];  /* 0x058 */
    u8 pad_1c8[0x2c];
    CEElem elems[2];      /* 0x1f4 */
    int f25c;             /* 0x25c */
    int f260;             /* 0x260 */
    s16 f264;             /* 0x264: selected kart slot (signed) */
    s16 f266;             /* 0x266: current elem index */
    int f268;             /* 0x268 */
} StructCE;               /* size 0x26c */

extern StructCE *data_0217ad08;

extern void Animation_Update(void *anim);
extern void *func_021a2398(void);  /* module:none lib call, probably char dst */
extern void *func_021a23ac(void);  /* module:none lib call, probably pltt dst */
extern void func_02078e4c(void *dst, void *plttDst);

void func_020783c8(void)
{
    StructCE *o = data_0217ad08;
    int slot = o->f264;

    if (slot < 0) {
        return;
    }
    Animation_Update(o->subs[slot].f08);

    /* the global is reloaded after the call (pointer may have moved) */
    o = data_0217ad08;
    if (o->elems[o->f266].f2c == 0) {
        /* nested calls: results go straight into r0/r1 of func_02078e4c */
        func_02078e4c(func_021a2398(), func_021a23ac());
    }
}
