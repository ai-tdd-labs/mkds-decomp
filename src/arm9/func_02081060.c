// PURPOSE: When a game object is switched on, this creates its controller and hooks it up.
// Takes one object (r0). If its enable-flag (+0x7C bit 0) is clear it does nothing.
// It also does nothing if a controller already exists for this object's slot
// (index +0x74) in the global controller table (*data_0217ae94). Otherwise it
// allocates a 0x80-byte controller from the allocator data_02155a14, stores it in
// the table at [slot], and initialises it: remembers the slot (+0x9B), clears a
// state field (+0x94 = 0), and installs func_02081b30 as its handler (+0x90).
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0[0x90];
    void *handler;      // +0x90 handler/update function pointer
    int state;          // +0x94 cleared to 0 on init
    u8 pad98[3];        // +0x98..0x9A
    u8 slot;            // +0x9B copy of the object's slot index
} Ctrl;

typedef struct {
    u8 pad0[0x74];
    u16 slot;           // +0x74 controller-table index
    u8 pad76[6];        // +0x76..0x7B
    int flags;          // +0x7C bit 0 = enabled
} Obj;

extern Ctrl **data_0217ae94;        // pointer to the controller table
extern char data_02155a14[];        // allocator/heap handle (passed by address)

extern void *func_0208b7bc(int size, void *heap);
extern void func_02081b30(void);    // installed as the controller's handler

void func_02081060(Obj *obj)
{
    Ctrl *c;

    if (!(obj->flags & 1)) return;
    if (data_0217ae94[obj->slot] != 0) return;

    data_0217ae94[obj->slot] = func_0208b7bc(0x80, data_02155a14);
    c = data_0217ae94[obj->slot];
    c->slot = (u8)obj->slot;
    c->state = 0;
    c->handler = func_02081b30;
}
