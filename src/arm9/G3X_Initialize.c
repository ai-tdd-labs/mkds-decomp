// PURPOSE: Initializes the Nintendo DS 3D graphics engine to its default state.
// Arguments: none.
// This clears pending geometry work, resets matrix state, and restores default 3D registers.
// It also clears the edge, fog, texture, and polygon settings used by later rendering.

typedef unsigned short u16;
typedef unsigned int u32;

extern void G3X_ClearFifo(void);
extern void G3X_InitializeMatrixStack(void);
extern void G3X_InitializeTable(void);

void G3X_Initialize(void)
{
    G3X_ClearFifo();

    *(volatile u32 *)0x04000504 = 0;
    while (*(volatile u32 *)0x04000600 & 0x08000000) {
    }

    *(volatile u16 *)0x04000060 = 0;
    *(volatile u32 *)0x04000600 = 0;
    *(volatile u32 *)0x04000010 = 0;

    *(volatile u16 *)0x04000060 |= 0x2000;
    *(volatile u16 *)0x04000060 |= 0x1000;
    *(volatile u16 *)0x04000060 &= ~0x3002;
    *(volatile u16 *)0x04000060 =
        (u16)((*(volatile u16 *)0x04000060 & ~0x3000) | 0x10);
    *(volatile u16 *)0x04000060 =
        (u16)(*(volatile u16 *)0x04000060 & (u16)~0x3004);

    *(volatile u32 *)0x04000600 |= 0x8000;
    *(volatile u32 *)0x04000600 =
        (*(volatile u32 *)0x04000600 & ~0xc0000000) | 0x80000000;

    G3X_InitializeMatrixStack();

    *(volatile u32 *)0x04000350 = 0;
    *(volatile u16 *)0x04000354 = 0x7fff;
    *(volatile u16 *)0x04000356 = 0;
    *(volatile u32 *)0x04000358 = 0;
    *(volatile u16 *)0x0400035c = 0;
    *(volatile u16 *)0x04000008 &= ~3;

    G3X_InitializeTable();

    *(volatile u32 *)0x040004a4 = 0x001f0080;
    *(volatile u32 *)0x040004a8 = 0;
    *(volatile u32 *)0x040004ac = 0;
}
