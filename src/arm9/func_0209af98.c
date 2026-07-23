/* PURPOSE: Resets a set of decay fields and rolls a fresh countdown timer for each active list entry.
 *
 * arg0 (mgr) points to a small manager: mgr->list is an array of entry
 * pointers, mgr->count is how many there are. For every non-null entry it
 * clears a block of fields, advances the entry's 64-bit random-number
 * generator one step, and stores a new value (30..89) into entry->0xa4.
 *
 * func_020d22d0(entry) returns a pointer to the entry's RNG state:
 * {u64 state; u64 mult; u64 inc;}. One LCG step is state = mult*state+inc,
 * then the high 32 bits scale to 30..89. (Same pattern/struct as the
 * sibling func_020930c8.)
 */

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u64 state;   /* 0x00 */
    u64 mult;    /* 0x08 */
    u64 inc;     /* 0x10 */
} Rng;

typedef struct {
    unsigned char pad0[0xa4];
    u32 out;              /* 0xa4 */
    unsigned char pad1[0xd0 - 0xa8];
    u16 f_d0;             /* 0xd0 */
    unsigned char pad2[0xdc - 0xd2];
    u32 f_dc;             /* 0xdc */
    u32 f_e0;              /* 0xe0 */
    u32 f_e4;              /* 0xe4 */
    u32 f_e8;              /* 0xe8 */
    u32 f_ec;              /* 0xec */
    unsigned char pad3[0x114 - 0xf0];
    u32 f_114;             /* 0x114 */
} Entry;

typedef struct {
    Entry **list;  /* 0x00 */
    u16 count;     /* 0x04 */
} Mgr;

extern Rng *func_020d22d0(void);

void func_0209af98(Mgr *mgr)
{
    int i;
    Entry *e;
    Rng *r;
    u32 hi;

    if (mgr == 0)
        return;

    i = 0;
    while (i < mgr->count && (e = mgr->list[i]) != 0) {
        e->f_d0 = 0;
        e->f_dc = 0;
        e->f_e0 = 0x1c7;
        e->f_e4 = 0;
        e->f_e8 = 0xe39;
        e->f_ec = 0;

        r = func_020d22d0();
        r->state = r->mult * r->state + r->inc;
        hi = (u32)(r->state >> 32);
        e->out = (u16)((u16)(((u64)hi * 60ULL) >> 32) + 0x1e);
        e->f_114 = 0;
        i++;
    }
}
