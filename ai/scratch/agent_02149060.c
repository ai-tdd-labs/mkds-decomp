// PURPOSE: Releases VRAM banks and returns their previous mask.
// The argument points to a halfword mask that is cleared by this routine.
// The released mask is added to the LCDC bank mask before the hardware update.

typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16 data_021802b0;
extern void GX_VRAMCNT_SetLCDC_(u32 mask);

u16 func_02149060(u16 *mask)
{
    u16 old_mask = *mask;

    *mask = 0;
    data_021802b0 |= old_mask;
    GX_VRAMCNT_SetLCDC_(old_mask);
    return old_mask;
}
