/*
 * PURPOSE: Marks one entry in a pool of kart-related objects as "selected" and clears
 * the same flag on every other entry.
 *
 * arg0 (r0): index of the entry that should become selected.
 * Calls func_02100138(0x6b) to get a pool descriptor: { void **list; unsigned short count; ... }.
 * If the pool lookup fails (returns NULL) the function does nothing and returns NULL.
 * Otherwise it walks list[0..count-1], stopping as soon as it reaches count OR
 * hits a NULL slot (whichever comes first). For each entry visited:
 *   - if its index equals arg0, entry->field_0xa0 = 0 and entry->field_0xa4 = 1 (select it)
 *   - otherwise entry->field_0xa4 = 0 (deselect it)
 * Returns the pool descriptor pointer.
 */

typedef struct Pool {
    void **list;
    unsigned short count;
} Pool;

typedef struct Entry {
    char pad_0[0xa0];
    int field_0xa0;
    int field_0xa4;
} Entry;

extern Pool *func_02100138(int id);

Pool *func_020a6cb4(int idx) {
    Pool *pool = func_02100138(0x6b);

    if (pool != 0) {
        int i;
        Entry *e;
        for (i = 0; i < pool->count && (e = (Entry *)pool->list[i]) != 0; i++) {
            if (i == idx) {
                e->field_0xa0 = 0;
                e->field_0xa4 = 1;
            } else {
                e->field_0xa4 = 0;
            }
        }
    }

    return pool;
}
