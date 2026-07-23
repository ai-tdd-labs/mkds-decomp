// PURPOSE: Selects the VRAM banks used for the clear-image buffer.
// The requested bank mask is saved in the shared graphics state.
// Active banks are removed from the LCDC mask and mapped to clear-image memory.

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct GXState {
    u16 lcdc;
    u16 bg;
    u16 obj;
    u16 arm7;
    u16 tex;
    u16 texPltt;
    u16 clrImg;
    u16 bgExtPltt;
    u16 objExtPltt;
    u16 sub_bg;
    u16 sub_obj;
    u16 sub_bgExtPltt;
    u16 sub_objExtPltt;
} GXState;

extern GXState data_021802b0;
extern void GX_VRAMCNT_SetLCDC_(u32 mask);

void func_021493b0(s32 clearimage)
{
    data_021802b0.lcdc =
        (u16)(~clearimage &
              (data_021802b0.lcdc | data_021802b0.clrImg));
    data_021802b0.clrImg = (u16)clearimage;

    switch (clearimage) {
    case 3:
        *(volatile u8 *)0x04000240 = 0x93;
    case 2:
        *(volatile u8 *)0x04000241 = 0x9b;
        *(volatile u16 *)0x04000060 |= 0x4000;
        break;
    case 12:
        *(volatile u8 *)0x04000242 = 0x93;
    case 8:
        *(volatile u8 *)0x04000243 = 0x9b;
        *(volatile u16 *)0x04000060 |= 0x4000;
        break;
    case 0:
        *(volatile u16 *)0x04000060 &= ~0x4000;
        break;
    case 1:
        *(volatile u8 *)0x04000240 = 0x9b;
        *(volatile u16 *)0x04000060 |= 0x4000;
        break;
    case 4:
        *(volatile u8 *)0x04000242 = 0x9b;
        *(volatile u16 *)0x04000060 |= 0x4000;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
