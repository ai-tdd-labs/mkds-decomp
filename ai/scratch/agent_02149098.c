// PURPOSE: Selects the VRAM bank for the sub-screen object extended palette.
// The selected bank is saved and removed from the active LCDC bank mask.
// Special bank values also update the sub-screen display and VRAM controls.

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

void GX_SetBankForSubOBJExtPltt(s32 subobjextpltt)
{
    data_021802b0.lcdc =
        (u16)(~subobjextpltt &
              (data_021802b0.lcdc | data_021802b0.sub_objExtPltt));
    data_021802b0.sub_objExtPltt = (u16)subobjextpltt;

    switch (subobjextpltt) {
    case 256:
        *(volatile u32 *)0x04001000 |= 0x80000000;
        *(volatile u8 *)0x04000249 = 0x83;
        break;
    case 0:
        *(volatile u32 *)0x04001000 &= ~0x80000000;
        break;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
