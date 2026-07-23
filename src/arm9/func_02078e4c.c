/* PURPOSE: Loads the kart emblem image and its colors into video memory.
 *
 * func_02078e4c(dst, plttDst): looks up the "kart_emblem" texture in the
 * texture dictionary of the currently selected kart's model resource
 * (data_0217ad08->subs[f264], holder field +0x14, resource file at +0x4)
 * and queues two VRAM transfers via AllocateReserveTEQSub:
 *   - cmd 0: texture image, offset (texImageParam & 0xffff) * 8, 0x200 bytes -> dst
 *   - cmd 1: palette, offset (u16 entry field +0x1c) * 16, 0x20 bytes -> plttDst
 * Does nothing when no kart is selected (f264 < 0) or when the lock word
 * (+0x2c) of the current elems[f266] entry is set. Probably the emblem
 * preview loader for the kart-select screen.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct StructCESub {
    u8 pad_00[0x14];
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
extern char data_02155018[]; /* "kart_emblem" */

extern int Dict_SomeFn_0(void *dict, char *name);
extern void AllocateReserveTEQSub(int cmd, u32 offset, void *dst, u32 size);

void func_02078e4c(void *dst, void *plttDst)
{
    StructCE *o = data_0217ad08;
    CEElem *e = &o->elems[o->f266];
    int slot = o->f264;
    u8 *res;
    u8 *dict;
    u8 *entbase;
    u32 eofs;
    u8 *ent;
    u32 esz;
    u8 *item;
    u32 plttOfs;
    int idx;

    if (slot < 0) {
        return;
    }
    if (e->f2c != 0) {
        return;
    }
    /* resource file (.nsbtx-like) of the selected kart's model holder */
    res = *(u8 **)((u8 *)o->subs[slot].f14 + 4);
    /* dictionary lives at res + *(res+8); lookup the emblem texture index */
    idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155018);
    dict = res + *(int *)(res + 8);         /* reload after the call */
    entbase = dict + 4;
    eofs = *(u16 *)(dict + 0xa);            /* offset of the entry block */
    ent = entbase + eofs;
    esz = *(u16 *)(entbase + eofs);         /* per-entry stride */
    item = dict + *(int *)(ent + esz * idx + 4);
    plttOfs = (u32)*(u16 *)(item + 0x1c) << 4;  /* survives the first call */
    AllocateReserveTEQSub(0, (*(u32 *)(item + 0x14) & 0xffff) << 3, dst, 0x200);
    AllocateReserveTEQSub(1, plttOfs, plttDst, 0x20);
}
