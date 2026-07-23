/*
 * PURPOSE: For every active entry in a list, either mark it "unset" or
 * compute a scaled value from a linked table entry and cache it.
 *
 * arg0 (list) points to a small header: a pointer to an array of object
 * pointers at +0x0 and a u16 element count at +0x4. For each non-null
 * element `obj` in that array:
 *   - obj->linked (+0x9c) is a pointer to another object; if that object's
 *     s16 field at +0x26 is negative, obj->cachedFlag (+0x100) is set to
 *     -1 (unset marker) and we move on.
 *   - Otherwise func_020d7da8 is called to fill obj->tablePtr (+0xf8) and
 *     obj->tableIndex (+0x104) (a pointer-to-array-base and an index into
 *     it, stride 0x54). obj->scale (+0xfc) is then set to 0x3000 (fixed
 *     point 3.0, 12-bit fraction). Finally obj->cachedValue (+0x108) is
 *     set to (table[idx].val * 0x3000) >> 12, i.e. that table field
 *     multiplied by 3.0 in fixed point, computed via a 64-bit
 *     intermediate product (matches the ROM's umull/mla sequence).
 */

typedef struct Linked {
    char pad[0x26];
    short flag26; /* +0x26: negative selects the "unset" path */
} Linked;

typedef struct TableEntry {
    char pad[0x34];
    int val34; /* +0x34: value to be scaled by 0x3000 (fixed 3.0) */
    char pad2[0x54 - 0x38]; /* stride is 0x54 */
} TableEntry;

typedef struct Obj {
    char pad00[0x9c];
    Linked *linked;      /* +0x9c */
    char pad_a0[0xf8 - 0xa0];
    TableEntry **tablePtr; /* +0xf8: pointer to base of stride-0x54 table */
    int scale;             /* +0xfc */
    unsigned short cachedFlag; /* +0x100 */
    short pad102;
    int tableIndex;        /* +0x104 */
    int cachedValue;        /* +0x108 */
} Obj;

typedef struct List {
    Obj **items; /* +0x0 */
    unsigned short count; /* +0x4 */
} List;

extern void func_020d7da8(void *out, void *linked, int flag);

void func_0209c4f0(List *list)
{
    int i;
    Obj *obj;
    if (list == 0) {
        return;
    }

    for (i = 0; i < list->count && (obj = list->items[i]) != 0; i++) {
        Linked *lk = obj->linked;
        if (lk->flag26 < 0) {
            obj->cachedFlag = 0xffff;
            continue;
        }

        func_020d7da8(&obj->tablePtr, lk, 0);
        obj->scale = 0x3000;

        {
            TableEntry *base = *obj->tablePtr;
            int idx = obj->tableIndex;
            int val = base[idx].val34;
            obj->cachedValue = (int)(((long long)val * 0x3000) >> 12);
        }
    }
}
