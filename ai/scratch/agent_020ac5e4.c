/* PURPOSE: Allocates and zero-initializes a small tracking record, tagging it with its owner.
 * Argument r0 (kept in r4) is an owner pointer stored into the new record.
 * Calls func_02100138(0x70) to allocate a 0x70-byte block, then func_0209bbfc()
 * (probably some kind of registration/list-insert that also returns the block
 * pointer, or NULL on failure). If that returns NULL, the function bails out
 * immediately without doing anything else. Otherwise it clears several fields
 * of the returned struct and stores the owner pointer at offset 0xac.
 */

extern void *func_02100138(int size);
extern void *func_0209bbfc(void);

void func_020ac5e4(void *arg0)
{
    void *entry = func_02100138(0x70);
    (void)entry;

    void *obj = func_0209bbfc();
    if (obj == 0) {
        return;
    }

    *(int *)((char *)obj + 0x4) = 0;
    *(int *)((char *)obj + 0x8) = 0;
    *(int *)((char *)obj + 0xc) = 0;
    *(int *)((char *)obj + 0x10) = 0;
    *(int *)((char *)obj + 0x14) = 0;
    *(int *)((char *)obj + 0x18) = 0;
    *(void **)((char *)obj + 0xac) = arg0;
    *(int *)((char *)obj + 0xa0) = 0;
    *(int *)((char *)obj + 0xa4) = 0;
    *(int *)((char *)obj + 0xa8) = 0;
    *(int *)((char *)obj + 0xb0) = 0;
}
