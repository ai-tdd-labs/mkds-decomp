// PURPOSE: Copies the current clipping matrix to the supplied buffer.
// The argument receives the 64-byte matrix data.
// It probably fails while the graphics hardware is busy.
// The source and status registers are fixed graphics hardware addresses.

extern void asm_MI_Copy64B(const void *src, void *dst);

int G3X_GetClipMtx(void *dst) {
    if (*(volatile unsigned int *)0x04000600 & 0x08000000) {
        return -1;
    }

    asm_MI_Copy64B((const void *)0x04000640, dst);
    return 0;
}
