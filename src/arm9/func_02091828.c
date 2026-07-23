/* PURPOSE: When triggered, resets a kart's status counters/vector fields and
 * flips on a status flag, then calls func_020d26f8.
 * arg0 = kart/object state, arg1 = race/global state (passed through
 * unchanged to func_020d26f8), arg2 = pointer to a "should activate?" byte,
 * arg3 = pointer to a byte that is returned.
 * If *arg2 == 1: set obj+0xb8 to a fixed mask (0x0000f333, a literal-pool
 * constant with no relocation, not a symbol), set obj+0xbc to 0x8000, clear
 * obj+0xb0 and obj+0xb4, OR a flag mask (read from data_02156458) into the
 * u16 status field at obj+0x2, set obj+0xc8 to 1, then call func_020d26f8.
 * Always returns *arg3. Sibling of func_02093b7c which has the same
 * arg0/activate/ret shape and also ends in a call to func_020d26f8. */

extern void func_020d26f8(void *a, void *b);

extern unsigned short data_02156458; /* u16 flag mask ORed into +0x2 */

struct Obj {
    char pad_00[0x2];
    unsigned short f2;   /* status flag bits */
    char pad_04[0xb0 - 0x4];
    unsigned int fb0;
    unsigned int fb4;
    unsigned int fb8;    /* fixed mask when activated */
    unsigned int fbc;    /* fixed 0x8000 when activated */
    char pad_c0[0xc8 - 0xc0];
    unsigned int fc8;
};

int func_02091828(struct Obj *obj, void *race,
                   unsigned char *activate, unsigned char *ret)
{
    unsigned char r = *ret;

    if (*activate == 1) {
        obj->fb8 = 0x0000f333;
        obj->fbc = 0x8000;
        obj->fb0 = 0;
        obj->fb4 = 0;
        obj->f2 |= data_02156458;
        obj->fc8 = 1;
        func_020d26f8(obj, race);
    }
    return r;
}
