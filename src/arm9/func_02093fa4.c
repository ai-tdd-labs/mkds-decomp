/* PURPOSE: Sets up a fresh game object's embedded sub-structure and
 * registers the object with a manager service.
 *
 * arg0 is the object being initialized. First it (re)initializes the
 * small structure embedded at offset 0xac using a count/handle value
 * taken from offset 0x9c (probably a list/queue node init), then runs a
 * second setup step on that same embedded structure. It then registers
 * the object with some kind of object/heap manager (id 0x1a2, size
 * 0x14 bytes) via func_020ac588. Finally it copies a shared config
 * value (data_0217ca6c->f164) into the object's field at offset 0x70,
 * probably a default classification/type value.
 */

typedef struct {
    unsigned char pad000[0x164];
    int f164; /* shared default classification value, copied into f70 */
} ConfigTable0217ca6c;

typedef struct {
    unsigned char pad000[0x70];
    int f70;            /* classification key, set from data_0217ca6c->f164 */
    unsigned char pad074[0x9c - 0x74];
    int f9c;            /* count/handle passed to the embedded-node init */
    unsigned char pad0a0[0xac - 0xa0];
    unsigned char fac;  /* start of an embedded sub-structure (opaque) */
} Obj02093fa4;

extern ConfigTable0217ca6c data_0217ca6c;

extern void func_020d7da8(void *node, int count, int flag);
extern void func_020d7d80(void *node);
extern void func_020ac588(int id, int size, void *obj);

void func_02093fa4(Obj02093fa4 *self)
{
    func_020d7da8(&self->fac, self->f9c, 0);
    func_020d7d80(&self->fac);

    func_020ac588(0x1a2, 0x14, self);

    self->f70 = data_0217ca6c.f164;
}
