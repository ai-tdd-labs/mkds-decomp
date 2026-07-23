// PURPOSE: Gets the current animation length in map-object units.
// The map object probably stores its animation handle at offset 0x28.
// The result is converted to the 16-bit value used by the caller.

extern unsigned int Animation_GetCurrentLength(void *animation);

unsigned int StructMapObject_SomeFn_2(void *map_object) {
    return (Animation_GetCurrentLength(*(void **)((char *)map_object + 0x28)) << 4) >> 16;
}
