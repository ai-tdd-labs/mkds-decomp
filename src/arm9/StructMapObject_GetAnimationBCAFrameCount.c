// PURPOSE: Gets the current frame count of a map object's animation.
// The object probably stores its animation pointer at offset 0x1C.
// The returned animation length is converted to the 16-bit frame value.

extern unsigned int Animation_GetCurrentLength(void *animation);

unsigned int StructMapObject_GetAnimationBCAFrameCount(void *object) {
    return (Animation_GetCurrentLength(*(void **)((char *)object + 0x1C)) << 4) >> 16;
}
