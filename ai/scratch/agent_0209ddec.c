/* PURPOSE: Starts a one-shot effect on an object, resetting its timers and
 * two child emitter structs, when told to activate.
 *
 * arg0 = object being configured, arg1 = race/global state, arg2 = pointer
 * to a "should activate?" byte, arg3 = pointer to a byte that is returned.
 * If *arg2 == 1 and the object's stage counter (+0xb8) is still 0 or 1:
 *   OR two flag masks into the u16 status field at +0x2, reset the stage
 *   counter to 2, set +0xa0/+0x10/+0x14/+0x18 to fixed values, reset the
 *   +0x70/+0x80 fields of the two child structs at +0xbc/+0xc0, and if the
 *   race mode (arg1+0x29c) is 1 or 3, OR a flag mask into +0x78. Finally
 *   calls func_020d26f8(obj, race). Always returns *arg3.
 */

extern void func_020d26f8(void *a, void *b);

extern unsigned short data_021565d8; /* u16 flag mask for +0x2 */
extern unsigned short data_021565dc; /* u16 flag mask for +0x2 */
extern unsigned int   data_021565e0; /* u32 flag mask for +0x78 */

struct Child {
    char pad_00[0x70];
    unsigned short f70;
    char pad_72[0x80 - 0x72];
    unsigned char f80;
};

struct Obj {
    char pad_00[0x2];
    unsigned short f2;
    char pad_04[0x10 - 0x4];
    int f10;
    int f14;
    int f18;
    char pad_1c[0x78 - 0x1c];
    int f78;
    char pad_7c[0xa0 - 0x7c];
    unsigned short fa0;
    char pad_a2[0xb8 - 0xa2];
    int fb8;
    struct Child *fbc;
    struct Child *fc0;
};

struct Race {
    char pad_000[0x29c];
    int f29c;
};

unsigned char func_0209ddec(struct Obj *obj, struct Race *race,
                             unsigned char *activate, unsigned char *ret)
{
    int r = *ret;

    if (*activate == 1) {
        if ((unsigned int)obj->fb8 <= 1) {
            int mode;

            obj->f2 |= data_021565d8;
            obj->f2 |= data_021565dc;

            obj->fb8 = 2;
            obj->fa0 = 0x168;
            obj->f10 = 0;
            obj->f14 = 0x3000;
            obj->f18 = 0;

            obj->fbc->f70 = 0x23;
            obj->fc0->f70 = 0x23;
            obj->fbc->f80 = 5;
            obj->fc0->f80 = 5;

            mode = race->f29c;
            if (mode == 1 || mode == 3) {
                obj->f78 |= data_021565e0;
            }

            func_020d26f8(obj, race);
        }
    }

    return (unsigned char)r;
}
