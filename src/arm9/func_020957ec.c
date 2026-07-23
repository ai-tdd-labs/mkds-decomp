/* PURPOSE: Applies a fixed forward-scaled offset to every object in a list, stopping at the first empty slot.
 *
 * Arg0 is a list container: a pointer to an array of object pointers (offset 0)
 * plus a u16 element count (offset 4). The function walks the array from index 0,
 * for each non-null entry it adds a fixed scale (0x320000, an fx32 constant) times
 * the entry's direction vector (offset 0x40) to the entry's base-position vector
 * (a VecFx32* stored at offset 0x9c), writing the result into the entry's own
 * output vector (offset 0xa4). The walk stops as soon as it hits a null slot
 * (probably a sparse/null-terminated pool) or once it reaches the count.
 * If arg0 itself is null the function does nothing.
 */

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    char pad40[0x40];
    VecFx32 dir;       /* +0x40: direction vector to add, scaled */
    char pad9c[0x9c - 0x40 - 0xc];
    VecFx32 *basePos;  /* +0x9c: pointer to the base position vector */
    char pada0[4];      /* +0xa0: unused padding */
    VecFx32 out;        /* +0xa4: result vector written by VecFx32_AddScale1 */
} Obj020957ec;

typedef struct {
    Obj020957ec **entries; /* +0x00: array of object pointers */
    unsigned short count;  /* +0x04: number of slots to scan */
} List020957ec;

extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base, VecFx32 *out);

void func_020957ec(List020957ec *list)
{
    int i;
    Obj020957ec *e;

    if (list == 0)
        return;

    for (i = 0; i < list->count && (e = list->entries[i]) != 0; i++) {
        VecFx32_AddScale1(0x320000, &e->dir, e->basePos, &e->out);
    }
}
