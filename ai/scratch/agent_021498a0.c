// PURPOSE: Selects the VRAM banks used for the main background extended palette.
// The requested bank mask is saved in the shared graphics state.
// Active banks are removed from the LCDC mask and mapped to palette memory.

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

void func_021498a0(s32 bgextpltt)
{
    data_021802b0.lcdc =
        (u16)(~bgextpltt &
              (data_021802b0.lcdc | data_021802b0.bgExtPltt));
    data_021802b0.bgExtPltt = (u16)bgextpltt;

    switch (bgextpltt) {
    case 0x10:
        *(volatile u32 *)0x04000000 |= 0x40000000;
        *(volatile u8 *)0x04000244 = 0x84;
        break;
    case 0x40:
        *(volatile u32 *)0x04000000 |= 0x40000000;
        *(volatile u8 *)0x04000246 = 0x8c;
        break;
    case 0x60:
        *(volatile u8 *)0x04000246 = 0x8c;
    case 0x20:
        *(volatile u8 *)0x04000245 = 0x84;
        *(volatile u32 *)0x04000000 |= 0x40000000;
        break;
    case 0:
        *(volatile u32 *)0x04000000 &= ~0x40000000;
        break;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
