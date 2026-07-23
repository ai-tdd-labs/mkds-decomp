/* PURPOSE: Loads one preset's data and spawns its on-screen items (probably
 * the racers/CPU markers on a menu or results screen).
 *
 * Arg: idx = which 16-byte preset entry to use.
 * First it copies the chosen 16-byte entry (4 pairs of shorts) from the
 * preset table into a small working buffer. It then fills any unused slots
 * (from a stored start-count up to 4) with -1 sentinels. Finally, for two
 * groups it creates up to 4 objects each via func_0208b60c and stamps each
 * one with position/id/side bytes taken from the working buffer.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct { short a, b; } Pair;
typedef struct { u16 v[8]; } WorkBuf;

typedef struct { int f0; int f4; } Sl;

typedef struct {
    char pad[0x90];
    int  f90;
    int  f94;
    u8   f98;
    u8   f99;
    u8   f9a;
    u8   f9b;
} Obj;

extern WorkBuf data_02155888[];
extern WorkBuf data_0217aea0;
extern int     data_0217ae98;
extern int     data_0217ae90;
extern Sl      data_02155808[];
extern u8      data_02155a14[];

extern Obj *func_0208b60c(int a, u8 *b);

void func_02082e4c(int idx)
{
    /* copy the whole 16-byte preset entry into the working buffer */
    data_0217aea0 = data_02155888[idx];

    /* fill unused slots (start..3) with -1 sentinels */
    {
        volatile int i = data_0217ae98;
        if (i < 4) {
            volatile int start = i;
            volatile int flag = data_0217ae90;
            Pair *arr = (Pair *)&data_0217aea0;
            do {
                if (i != start || flag == 0)
                    arr[i].a = -1;
                arr[i].b = -1;
                i++;
            } while (i < 4);
        }
    }

    /* for two groups, spawn up to 4 objects each */
    {
        Sl *sl = data_02155808;
        volatile int sel1 = 1;
        volatile int sel0 = 0;
        volatile int cnt0 = 0;
        int fp;
        for (fp = 0; fp < 2; fp++) {
            Pair *sb = (Pair *)&data_0217aea0;
            volatile int j = cnt0;
            u8 side = (u8)(fp ? sel1 : sel0);
            for (;;) {
                Obj *o;
                if (sb->a < 0)
                    break;
                o = func_0208b60c(sl->f0, data_02155a14);
                o->f90 = sl->f4;
                o->f98 = (u8)sb->a;
                {
                    short t = sb->b;
                    sb++;
                    o->f99 = t < 0 ? (u8)0xff : (u8)t;
                }
                o->f9a = side;
                o->f9b = 0;
                o->f94 = 0;
                if (++j >= 4)
                    break;
            }
            sl++;
        }
    }
}
