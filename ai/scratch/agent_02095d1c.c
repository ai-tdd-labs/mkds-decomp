/* PURPOSE: Runs one update step over a list of active objects, moving each one.
 *
 * Argument r0 is a small "list" header: word 0 is a pointer to an array of
 * object pointers, halfword 4 is how many entries the array has. For every
 * non-NULL entry the code reads a signed 16-bit speed/value from a sub-object,
 * scales it (<<12) and divides by 100 to make a fixed-point step, stores that
 * step in the object (+0xa8), then calls func_020e516c to apply the movement.
 * Returns immediately if the list pointer is NULL. (field names are guesses.)
 */

typedef short s16;
typedef unsigned short u16;

typedef struct {
    void **entries; /* +0x00: array of object pointers */
    u16   count;    /* +0x04: number of entries */
} ObjList;

/* thumb callee: apply movement to object (dst = obj+0xdc, src = obj+4) */
extern void func_020e516c(void *dst, void *src, int a2, int a3);

void func_02095d1c(ObjList *list)
{
    int i;
    void *e;

    if (list == 0)
        return;

    for (i = 0; i < list->count && (e = list->entries[i]) != 0; i++) {
        void *o = *(void **)((char *)e + 0x9c);   /* sub-object */
        int v = *(s16 *)((char *)o + 0x28);       /* signed 16-bit value */
        int sb = v << 12;                          /* to fixed-point */
        *(int *)((char *)e + 0xa8) = sb / 100;     /* store step */
        func_020e516c((char *)e + 0xdc, (char *)e + 4, 0x54666, 0xe);
    }
}
