/*
 * PURPOSE: Find the first entry in the current map-object pointer array whose flags have bit 0x100 set.
 */

typedef struct MapObjectFlags {
    unsigned short pad0;
    unsigned short flags;
} MapObjectFlags;

extern void *func_02100138(int id);
extern void **func_0210008c(void);
extern int func_021000c8(void *holder);

void *func_020ac524(int id)
{
    void *holder = func_02100138(id);
    void **array = func_0210008c();
    int count = func_021000c8(holder);
    int i;

    for (i = 0; i < count; i++) {
        void *entry = array[i];
        MapObjectFlags *flagObj = (MapObjectFlags *)entry;
        if (flagObj->flags & 0x100) {
            return entry;
        }
    }
    return 0;
}
