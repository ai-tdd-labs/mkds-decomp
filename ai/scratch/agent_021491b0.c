// PURPOSE: Updates the LCDC VRAM bank mask and related hardware settings.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct VramMaskState {
    u16 active_mask;
    u8 padding_02[0x12];
    u16 saved_mask;
} VramMaskState;

extern volatile VramMaskState data_021802b0;
extern void GX_VRAMCNT_SetLCDC_(u32 mask);

void func_021491b0(u16 mask)
{
    u16 saved_mask = data_021802b0.saved_mask;

    data_021802b0.saved_mask = mask;
    data_021802b0.active_mask &= ~(mask | saved_mask);

    if (mask != 0) {
        if (mask == 8) {
            *(volatile u8 *)0x04000243 = 0x84;
        } else if (mask == 0x100) {
            *(volatile u8 *)0x04000249 = 0x82;
        }
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.active_mask);
}
