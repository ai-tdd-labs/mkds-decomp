/*
 * PURPOSE: find the first live element of a MapObject pointer array that has its 0x100 flag set and dispatch it.
 */

typedef struct MapObjectPtrArray {
    void **list;
    unsigned short count;
} MapObjectPtrArray;

typedef struct MapObjectFlags {
    unsigned short pad0;
    unsigned short flags;
} MapObjectFlags;

extern void *func_020d233c(void *obj);

void *func_0209bbfc(MapObjectPtrArray *array)
{
    int i;
    void *obj;

    if (array == 0) {
        goto not_found;
    }

    for (i = 0; i < array->count && (obj = array->list[i]) != 0; i++) {
        MapObjectFlags *flagObj = (MapObjectFlags *)obj;
        if (flagObj->flags & 0x100) {
            func_020d233c(obj);
            return obj;
        }
    }

not_found:
    return 0;
}
