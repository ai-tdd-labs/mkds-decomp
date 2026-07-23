// PURPOSE: Returns the current length value for a map object.
// If the object has a linked entry, it returns that entry's stored value.
// Otherwise it returns zero without a secondary entry, or derives a value
// from the object's animation, probably for map-object timing.

typedef struct MapObjectLinkedEntry {
    unsigned char padding_00[0x1a];
    unsigned short value_1a;
} MapObjectLinkedEntry;

typedef struct MapObject {
    unsigned char padding_00[0x0c];
    MapObjectLinkedEntry *linked_entry;
    void *secondary_entry;
    unsigned char padding_14[0x0c];
    void *animation;
} MapObject;

extern unsigned int Animation_GetCurrentLength(void *animation);

unsigned int StructMapObject_SomeFn_1(MapObject *map_object)
{
    if (map_object->linked_entry != 0) {
        return map_object->linked_entry->value_1a;
    }

    if (map_object->secondary_entry == 0) {
        return 0;
    }

    return (Animation_GetCurrentLength(map_object->animation) << 4) >> 16;
}
