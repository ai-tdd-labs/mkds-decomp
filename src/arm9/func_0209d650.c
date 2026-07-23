/* PURPOSE: Initializes a fresh object's embedded list node and registers
 * the object with an object/heap manager, then clears three tracking
 * fields.
 *
 * arg0 is the object being initialized. It (re)initializes the small
 * node structure embedded at offset 0xb8 using a count/handle value
 * taken from offset 0x9c (list/queue node init), then registers the
 * object with an object/heap manager (id 0x1ae, size 0x1e bytes) via
 * func_020ac588. Finally it clears the fields at offsets 0x10, 0x14,
 * and 0x18 to zero (probably counters/handles reset for a fresh
 * object).
 */

typedef struct {
    unsigned char pad000[0x10];
    int f10; /* cleared to 0 */
    int f14; /* cleared to 0 */
    int f18; /* cleared to 0 */
    unsigned char pad01c[0x9c - 0x1c];
    int f9c;            /* count/handle passed to the embedded-node init */
    unsigned char pad0a0[0xb8 - 0xa0];
    unsigned char fb8;  /* start of an embedded sub-structure (opaque) */
} Obj0209d650;

extern void func_020d7da8(void *node, int count, int flag);
extern void func_020ac588(int id, int size, void *obj);

void func_0209d650(Obj0209d650 *self)
{
    func_020d7da8(&self->fb8, self->f9c, 0);

    func_020ac588(0x1ae, 0x1e, self);

    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
}
