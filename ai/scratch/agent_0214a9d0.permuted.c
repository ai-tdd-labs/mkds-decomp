// PURPOSE: Resets the geometry engine's matrix stack and default rendering state.
typedef unsigned short u16;
typedef unsigned int u32;

extern void G3X_ResetMatrixStack2(void);

void G3X_ResetMatrixStack(void)
{
    while (*(volatile u32 *)0x04000600 & 0x08000000) {
    }
    *(volatile u32 *)0x04000600 |= 0x8000;
    *(volatile u16 *)0x04000060 |= 0x2000;
    *(volatile u16 *)0x04000060 |= 0x1000;
    G3X_ResetMatrixStack2();
    *(volatile u32 *)0x040004a4 = 0x021f0080;
    *(volatile u32 *)0x040004a8 = 0;
    *(volatile u32 *)0x040004ac = 0;
}
