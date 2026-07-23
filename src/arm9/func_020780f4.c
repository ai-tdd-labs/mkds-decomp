/* PURPOSE: Starts loading the currently selected kart's model data.
 *
 * Reads the global kart-select work object (data_0217ad08). If a kart slot
 * is selected (f264 >= 0) and both request words (+0x24 and +0x28) are
 * valid (not -1), it kicks off a load via func_020787f4 with the request's
 * handle (+0x50) and a global heap/context pointer (data_021656ec), then
 * sets up the selected slot's sub-object with func_02078580 and finally
 * calls an ITCM helper. Probably part of the kart-select screen model
 * streaming. Field meanings are uncertain ("probably").
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct CEReq {
    int f0;               /* 0x24: request word, -1 = invalid */
    int f4;               /* 0x28: second request word, -1 = invalid */
    u8 pad_08[0x24];
    int f2c;              /* 0x50: handle passed to func_020787f4 */
} CEReq;

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
    u8 pad_00[0x24];
    CEReq req;            /* 0x024 */
    u8 pad_54[4];
    StructCESub subs[2];  /* 0x058 */
    u8 pad_1c8[0x1c];
    int f1e4;             /* 0x1e4: third arg for func_02078580 */
    u8 pad_1e8[0xc];
    CEElem elems[2];      /* 0x1f4 */
    int f25c;             /* 0x25c */
    int f260;             /* 0x260 */
    s16 f264;             /* 0x264: selected kart slot (signed) */
    s16 f266;             /* 0x266: current elem index */
    int f268;             /* 0x268 */
} StructCE;               /* size 0x26c */

extern StructCE *data_0217ad08;
extern int data_021656ec; /* probably a heap/context pointer */

extern void func_020787f4(int handle, int ctx);
extern void func_02078580(StructCESub *sub, CEReq *req, int arg);
extern void func_01ff9234(void); /* ITCM helper, unsymbolized */

void func_020780f4(void)
{
    StructCE *o = data_0217ad08;
    int slot = o->f264;
    StructCESub *sub;
    CEReq *q;

    if (slot < 0) {
        return;
    }
    sub = &o->subs[slot];
    q = &o->req;                 /* pointer taken before the first read */
    if (o->req.f0 == -1) {       /* first read via the base pointer */
        return;
    }
    if (q->f4 == -1) {
        return;
    }
    func_020787f4(q->f2c, data_021656ec);
    o = data_0217ad08;           /* reload the global after the call */
    func_02078580(sub, &o->req, o->f1e4);
    func_01ff9234();
}
