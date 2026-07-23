/*
 * PURPOSE: Reset the b4/b8 fields to zero for every entry in an object's pointer array, stopping at the first null entry.
 */

struct ObjArrayHolder {
    void **array;        /* offset 0x0: array of entry pointers */
    unsigned short count; /* offset 0x4: number of entries in array */
};

struct ArrayEntry {
    unsigned char pad[0xb4];
    int field_0xb4;
    int field_0xb8;
};

extern struct ObjArrayHolder *func_02100138(int id);

void func_020946b8(void)
{
    struct ObjArrayHolder *holder = func_02100138(0x13b);
    int i;
    struct ArrayEntry *entry;

    if (holder == 0) {
        return;
    }

    i = 0;
    goto check;
body:
    entry->field_0xb4 = 0;
    entry->field_0xb8 = 0;
    i++;
check:
    if (i >= holder->count) {
        return;
    }
    entry = (struct ArrayEntry *)holder->array[i];
    if (entry != 0) {
        goto body;
    }
}
