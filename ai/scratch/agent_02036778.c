// PURPOSE: Enables the vertical blank interrupt for the graphics system.
// It installs the game's VBlank handler and enables its interrupt source.
// The hardware register write probably acknowledges the pending VBlank state.

typedef unsigned short u16;
typedef unsigned int u32;

extern void VblankIRQHandler(void);
extern void Os_SetIrqHandler(u32 mask, void (*handler)(void));
extern u32 Os_EnableIrqHandler(u32 mask);
extern u32 Os_EnableIrq(u32 mask);
extern void GX_VBlankIntr(u32 param);

void EnableVblankIRQ(void)
{
    Os_SetIrqHandler(1, VblankIRQHandler);
    Os_EnableIrqHandler(1);
    *(volatile u16 *)0x04000208;
    *(volatile u16 *)0x04000208 = 1;
    Os_EnableIrq(1);
    GX_VBlankIntr(1);
}
