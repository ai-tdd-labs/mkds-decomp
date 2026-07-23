/* PURPOSE: Resets each active item/kart entry in a group to full scale and
   recomputes two derived size values from its base size field.

   Arg0 (g) points to a group: a pointer to an array of entry pointers (offset
   0) and a u16 count (offset 4). For every entry in the array (stopping at the
   count or at the first NULL slot) it forces two fixed-point fields to 1.0,
   then derives fx32 values at 0xc0 (base * 0xf333 >> 12) and 0xc4
   (base * 2.0), and copies the 0xc0 result into 0xb8.
   Probably a per-frame or reset pass over a group of objects. */

typedef int fx32;
typedef long long fx64;

typedef struct Entry {
    char pad00[0x20];
    fx32 f20;              /* 0x20 base size (fx32) */
    char pad24[0xb0 - 0x24];
    fx32 fb0;             /* 0xb0 */
    fx32 fb4;             /* 0xb4 */
    fx32 fb8;             /* 0xb8 */
    char padbc[0xc0 - 0xbc];
    fx32 fc0;            /* 0xc0 */
    fx32 fc4;            /* 0xc4 */
} Entry;

typedef struct Group {
    Entry **entries;          /* 0x0 */
    unsigned short count;     /* 0x4 */
} Group;

void func_0209151c(Group *g) {
    int i;
    Entry *e;

    if (g == 0)
        return;
    i = 0;
    while (i < g->count && (e = g->entries[i]) != 0) {  /* stop at count or empty slot */
        e->fb0 = 0x1000;                                /* 1.0 */
        e->fb4 = 0x1000;                                /* 1.0 */
        e->fc0 = (fx32)(((fx64)e->f20 * 0xf333) >> 12); /* base * 0xf333 (fx) */
        e->fc4 = (fx32)(((fx64)e->f20 * 0x2000) >> 12); /* base * 2.0 -> base << 1 */
        e->fb8 = e->fc0;                                /* reloaded from 0xc0 */
        i++;
    }
}
