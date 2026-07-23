// PURPOSE: Spawns/refreshes the on-screen animation objects for each item in a
// racer's list whenever that item's stored value changed.
// arg0 = a list (u16 count, then one u32 value per entry at +4, stride 4).
// arg1 = a small id byte stored into each new object (+0x98).
// arg2 = the Racer this list belongs to (has u16 animation-index at +0x74).
// For every entry whose current value differs from the one cached in the racer's
// animation-entry table, it flags any two existing sub-objects as "counter enabled",
// updates the cache, then builds 2 fresh animation objects via func_0208b7bc and
// fills in their owner racer, sub-index, id byte and a shared callback pointer.

typedef int fx32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad90[0x90];
    void *f90;   // shared callback / vtable pointer (func_020831bc)
    void *f94;   // owner racer (arg2)
    u8   f98;    // id byte (arg1)
    u8   f99;    // "counter enabled" flag
    char pad9b[0x9b - 0x9a];
    u8   f9b;    // sub-entry index (0 or 1)
} T;

typedef struct {
    char pad74[0x74];
    u16 f74;     // animation entry index
} Racer;

typedef struct {
    u16 count;
} List;

extern u8 *data_0217ae84;          // bss slot holding base of racer-entry array (stride 0x58)
extern char data_02155a14[];       // config/template passed to the builder
extern void *func_0208b7bc(u32 v, void *cfg);
extern void func_020831bc(void);   // used only as a stored pointer value

int func_02083ae0(List *list, int a1, Racer *r)
{
    u16 i;
    u16 j;
    void *cb;                            // pool address held across the whole loop
    volatile int zero;
    volatile int one;
    u8 **dbase;                          // pool address held across the whole loop

    i = 0;
    if (list->count == 0)
        return 0;

    dbase = &data_0217ae84;
    cb = (void *)func_020831bc;
    zero = 0;
    one = 1;

    do {
        u8 *entry = *dbase + (u32)r->f74 * 0x58;
        u32 va = ((u32 *)((u8 *)list + 4))[i];
        j = zero;
        if (va != *(u32 *)(entry + i * 4 + 4)) {
            u32 *cache = (u32 *)(entry + i * 4);
            T *p1 = *(T **)(entry + i * 8 + 0x10);
            if (p1 != 0)
                p1->f99 = (u8)one;
            T *p2 = *(T **)(entry + i * 8 + 0x14);
            if (p2 != 0)
                p2->f99 = (u8)one;
            cache[1] = ((u32 *)list)[i + 1];
            do {
                u32 v = cache[1];
                T *res = (T *)func_0208b7bc(v, data_02155a14);
                u8 *e2 = *dbase + (u32)r->f74 * 0x58;
                *(T **)(e2 + i * 8 + j * 4 + 0x10) = res;
                res->f94 = (void *)r;
                res->f9b = (u8)j;
                res->f98 = a1;
                res->f90 = cb;
                j++;
            } while (j < 2);
        }
        i++;
    } while (i < list->count);

    return one;
}
