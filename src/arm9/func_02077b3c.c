/* PURPOSE: Commits the pending kart-select change and schedules the worker task that applies it.
 *
 * No arguments. If either request flag (+0x25c / +0x260) is set, it locks the
 * current elems[f266] entry, copies the pending values f24/f28 into the target
 * object at f20 (fields +0 and +4), points the target's +0x20 at entry f28 of
 * the 0xe0-stride table at f1c8, queues func_02077d68 on the worker, and
 * raises the worker taskPending flag.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct StructT {
    int f00;              /* 0x00 */
    int f04;              /* 0x04 */
    u8 pad_08[0x18];
    void *f20;            /* 0x20: pointer into the 0xe0-stride table */
} StructT;

typedef struct ElemE0 {
    u8 pad_00[0xe0];
} ElemE0;                 /* size 0xe0 */

typedef struct StructCESub {
    u8 pad_00[0x08];
    void *f08;            /* 0x08 */
    u8 pad_0c[0x08];
    void *f14;            /* 0x14 */
    u8 pad_18[0xa0];
} StructCESub;            /* size 0xb8 */

typedef struct CEElem {
    u8 pad_00[0x2c];
    int f2c;              /* 0x2c: lock/busy word */
    u8 pad_30[4];
} CEElem;                 /* size 0x34 */

typedef struct StructCE {
    u8 pad_00[0x20];
    StructT *f20;         /* 0x20: target object */
    int f24;              /* 0x24: pending value A */
    int f28;              /* 0x28: pending value B / table index */
    u8 pad_2c[0x2c];
    StructCESub subs[2];  /* 0x058 */
    ElemE0 *f1c8;         /* 0x1c8: 0xe0-stride table */
    u8 pad_1cc[0x28];
    CEElem elems[2];      /* 0x1f4 */
    int f25c;             /* 0x25c: request flag A */
    int f260;             /* 0x260: request flag B */
    s16 f264;             /* 0x264 */
    s16 f266;             /* 0x266: current elem index */
    int f268;             /* 0x268 */
} StructCE;               /* size 0x26c */

typedef struct SaveWorkerState {
    u8 pad_00[0xf8];
    u32 taskPending;      /* 0xf8 */
} SaveWorkerState;

extern StructCE *data_0217ad08;
extern SaveWorkerState *data_0217aa0c;

extern void WorkerInsertTask(void (*task)(void));
extern void func_02077d68(void);

void func_02077b3c(void)
{
    StructCE *o = data_0217ad08;

    if (o->f25c != 0 || o->f260 != 0) {
        data_0217ad08->elems[data_0217ad08->f266].f2c = 1;
        data_0217ad08->f20->f00 = data_0217ad08->f24;
        data_0217ad08->f20->f04 = data_0217ad08->f28;
        data_0217ad08->f20->f20 = &data_0217ad08->f1c8[data_0217ad08->f28];
        WorkerInsertTask(func_02077d68);
        data_0217aa0c->taskPending = 1;
    }
}
