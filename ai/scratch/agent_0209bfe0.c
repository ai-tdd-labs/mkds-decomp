/* PURPOSE: Sets up a fresh object's particle/effect config the first time
 * it's used, then fires a classification event for it.
 *
 * arg0 is passed through to func_02100138/func_0209bc5c to resolve/allocate
 * the target object (self). If self has already been initialized (f11c
 * nonzero), the function returns 0 immediately. Otherwise it fills in a
 * block of default fields (b8..f4), marks it initialized (f11c=1), and
 * unless flag bit 0x4 of f78 is set, classifies self->f70 against the
 * shared config table (data_0217ca6c) and dispatches an event describing
 * it via func_020d4ef4/func_0210b7a8. Returns 1 on the normal path.
 */

typedef struct {
    unsigned char pad000[0x68];
    int f68; /* classification value 1 */
    unsigned char pad06c[0x8c - 0x6c];
    int f8c; /* classification value 2 */
} ConfigTable209f6d8;

extern ConfigTable209f6d8 data_0217ca6c;

typedef struct {
    unsigned char pad000[0x70];
    int f70;   /* classification key, compared against data_0217ca6c fields */
    unsigned char pad074[4];
    int f78;   /* flags; bit 0x4 suppresses the event */
    unsigned char pad07c[0xb8 - 0x7c];
    unsigned short fb8;
    unsigned char pad0ba[0xc4 - 0xba];
    int fc4;
    int fc8;
    int fcc;
    int fd0;
    int fd4;
    unsigned short fd8;
    unsigned char pad0da[0xe4 - 0xda];
    int fe4;
    int fe8;
    int fec;
    int ff0;
    int ff4;
    unsigned char pad0f8[0x11c - 0xf8];
    int f11c; /* nonzero once this object has already been initialized */
} Obj0209bfe0;

extern void *func_02100138(int id);
extern Obj0209bfe0 *func_0209bc5c(void *unused0, int index);
extern int func_020d4ef4(void *addr, int kind);
extern void func_0210b7a8(void *args);

int func_0209bfe0(int arg0)
{
    Obj0209bfe0 *self;

    /* Nested call: func_02100138's result is passed straight through as
     * the first argument to func_0209bc5c without being saved. */
    self = func_0209bc5c(func_02100138(0x1a8), arg0);

    if (self->f11c != 0) {
        goto already_init;
    }

    self->fb8 = 0x8000;
    self->fc4 = 0x1000;
    self->fc8 = 0x400;
    self->fcc = ~0x28;
    self->fd0 = 0x1000;
    self->fd4 = 0;
    self->fd8 = 0;
    self->fe4 = 0x1000;
    self->fe8 = 0x400;
    self->fec = ~0x28;
    self->ff0 = 0x1000;
    self->ff4 = 0;
    self->f11c = 1;

    if ((self->f78 & 4) == 0) {
        int kind;
        void *addr;
        int args[4];
        const int eventKind = 463;

        if (self->f70 == data_0217ca6c.f68) {
            kind = 2;
        } else if (self->f70 == data_0217ca6c.f8c) {
            kind = 3;
        } else {
            kind = 4;
        }

        addr = (char *)self + 4;

        args[0] = eventKind;
        args[1] = (int)addr;
        args[2] = kind;
        args[3] = func_020d4ef4(addr, eventKind);

        func_0210b7a8(args);
    }

    return 1;

already_init:
    return 0;
}
