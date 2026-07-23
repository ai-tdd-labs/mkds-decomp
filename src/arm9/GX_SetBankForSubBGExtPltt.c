// PURPOSE: Selects the VRAM bank for the sub-screen background extended palette.
// The requested bank is removed from the LCDC mask and saved in the shared
// graphics state. Special selections also update the sub-screen display and
// VRAM control registers.

typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

void GX_SetBankForSubBGExtPltt(s32 subbgextpltt)
{
    data_021802b0.lcdc =
        (u16)(~subbgextpltt &
              (data_021802b0.lcdc | data_021802b0.sub_bgExtPltt));
    data_021802b0.sub_bgExtPltt = (u16)subbgextpltt;

    switch (subbgextpltt) {
    case 128:
        *(volatile u32 *)0x04001000 |= 0x40000000;
        *(volatile u8 *)0x04000248 = 0x82;
        break;
    case 0:
        *(volatile u32 *)0x04001000 &= ~0x40000000;
        break;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
