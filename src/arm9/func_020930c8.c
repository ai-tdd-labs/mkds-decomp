/* PURPOSE: Rolls a fresh random timer value for each active item in a list.
 *
 * arg0 (mgr) points to a small manager: mgr->list is an array of entry
 * pointers, mgr->count is how many there are. For every entry whose flag
 * bit 0x800 is set, it advances that entry's 64-bit random-number
 * generator one step and stores a new value (200..224) into entry->0xa4.
 *
 * func_020d22d0(entry) probably returns a pointer to the entry's RNG
 * state: {u64 state; u64 mult; u64 inc;}. One LCG step is
 * state = mult*state + inc, then the high 32 bits scale to 0..24.
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
    u16 pad0;    /* 0x00 */
    u16 flags;   /* 0x02 */
    u16 pad[0x50]; /* fill up to 0xa4 */
    u32 out;     /* 0xa4 */
} Entry;

typedef struct {
    Entry **list; /* 0x00 */
    u16 count;    /* 0x04 */
} Mgr;

extern Rng *func_020d22d0(void);

void func_020930c8(Mgr *mgr)
{
    int i;
    Entry *e;
    Rng *r;
    u32 hi;

    if (mgr == 0)
        return;

    for (i = 0; i < mgr->count && (e = mgr->list[i]) != 0; i++) {
        if (e->flags & 0x800) {
            r = func_020d22d0();
            r->state = r->mult * r->state + r->inc;
            hi = (u32)(r->state >> 32);
            e->out = (u16)((u16)(((u64)hi * 25) >> 32) + 0xc8);
        }
    }
}
