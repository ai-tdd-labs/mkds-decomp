// PURPOSE: Copies the current 3D vector matrix to the caller.
// Arguments: destination pointer for the 36-byte matrix.
// Returns -1 while the graphics engine is busy, otherwise returns 0.
// The matrix source is probably the fixed geometry register block.

extern void asm_MI_Copy36B(const void *src, void *dst);

int G3X_GetVectorMtx(void *dst) {
    if (*(volatile unsigned int *)0x04000600 & 0x08000000) {
        return -1;
    }

    asm_MI_Copy36B((void *)0x04000680, dst);
    return 0;
}
