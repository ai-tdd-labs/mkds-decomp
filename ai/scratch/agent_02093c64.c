/* PURPOSE: Initializes an object for its "active" behavior state: marks it visible via a
 * global flag bit, tears down its old lifetime state, allocates/initializes its sound
 * handle, starts a sound on that handle, and wires its owning sub-object's update
 * function pointer to a fixed handler.
 *
 * Field layout mirrors the Obj struct used by func_02093910.c (same object type):
 *   flags at +0x2 (u16), sub-object pointer at +0x94, soundHandle at +0xa8.
 * The sub-object has a function-pointer slot at +0x30 that gets pointed at
 * func_0210a6b4 (a fixed per-mode update routine).
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad30[0x30];
    void (*updateFunc)(void);   /* +0x30: update handler for this sub-object */
} Sub;

typedef struct {
    u16 f0;
    u16 flags;                  /* +0x02 */
    char pad4[0x94 - 0x4];
    Sub *sub;                   /* +0x94: owning sub-object */
    char pad98[0xa8 - 0x98];
    int soundHandle;            /* +0xa8 */
} Obj;

extern volatile u16 data_021564b4;

extern void func_020d2398(Obj *obj);
extern int  func_020d286c(Obj *obj);
extern void func_0210b850(int soundHandle);
extern void func_0210a6b4(void);

void func_02093c64(Obj *obj)
{
    obj->flags |= data_021564b4;

    func_020d2398(obj);

    obj->soundHandle = func_020d286c(obj);
    func_0210b850(obj->soundHandle);

    obj->sub->updateFunc = func_0210a6b4;
}
