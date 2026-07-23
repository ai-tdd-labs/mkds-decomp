/* PURPOSE: When an item/effect is triggered, shrinks a kart's size vector and
 * flips on some status flags.
 * arg0 = kart/object state, arg1 = race/global state, arg2 = pointer to a
 * "should activate?" byte, arg3 = pointer to a byte that is returned.
 * If *arg2 == 1: set two counters (0xa0=0x78, 0xa4=1), scale the three
 * components of the fx32 vector at +0x10/+0x14/+0x18 down by 1/4 (FX_Mul by
 * 0x400), then force the middle component (+0x14) to 0x4000; OR a flag mask
 * into the u16 at +0x2; if the race mode (arg1+0x29c) is 1 or 3, OR another
 * mask into the u32 at +0x78; finally call func_020d26f8. Always returns *arg3. */

extern void func_020d26f8(void *a, void *b);

extern unsigned short data_021564ac; /* u16 flag mask for +0x2 */
extern unsigned int   data_021564b0; /* u32 flag mask for +0x78 */

struct Obj {
    char pad_00[0x2];
    unsigned short f2;      /* status flag bits */
    char pad_04[0x10 - 0x4];
    int f10;               /* fx32 vector x */
    int f14;               /* fx32 vector y */
    int f18;               /* fx32 vector z */
    char pad_1c[0x78 - 0x1c];
    unsigned int f78;      /* status flag bits (wide) */
    char pad_7c[0xa0 - 0x7c];
    int fa0;
    int fa4;
};

struct Race {
    char pad_000[0x29c];
    int f29c;              /* race mode */
};

int func_02093b7c(struct Obj *obj, struct Race *race,
                  unsigned char *activate, unsigned char *ret)
{
    unsigned char r = *ret;

    if (*activate == 1) {
        obj->fa0 = 0x78;
        obj->fa4 = 1;
        obj->f10 = (int)(((long long)obj->f10 * 0x400) >> 12);
        obj->f14 = (int)(((long long)obj->f14 * 0x400) >> 12);
        obj->f18 = (int)(((long long)obj->f18 * 0x400) >> 12);
        obj->f14 = 0x4000;
        obj->f2 |= data_021564ac;
        if (race->f29c == 1 || race->f29c == 3) {
            obj->f78 |= data_021564b0;
        }
        func_020d26f8(obj, race);
    }
    return r;
}
