// PURPOSE: Selects the VRAM bank for the sub-screen background.

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

void func_0214922c(s32 subbg)
{
    data_021802b0.lcdc =
        (u16)(~subbg & (data_021802b0.lcdc | data_021802b0.sub_bg));
    data_021802b0.sub_bg = (u16)subbg;

    switch (subbg) {
    case 4:
        *(volatile u8 *)0x04000242 = 0x84;
        break;
    case 128:
        *(volatile u8 *)0x04000248 = 0x81;
        break;
    case 384:
        *(volatile u8 *)0x04000249 = 0x81;
        break;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
