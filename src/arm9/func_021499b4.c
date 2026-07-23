// PURPOSE: Selects the VRAM banks used for object graphics.
// The requested bank mask is saved in the shared graphics state.
// Active banks are removed from the LCDC mask and mapped to object memory.

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

void func_021499b4(s32 obj)
{
    data_021802b0.lcdc =
        (u16)(~obj & (data_021802b0.lcdc | data_021802b0.obj));
    data_021802b0.obj = (u16)obj;

    switch (obj) {
    case 3:
        *(volatile u8 *)0x04000241 = 0x8a;
    case 1:
        *(volatile u8 *)0x04000240 = 0x82;
    case 0:
        break;
    case 2:
        *(volatile u8 *)0x04000241 = 0x82;
        break;
    case 112:
        *(volatile u8 *)0x04000246 = 0x9a;
    case 48:
        *(volatile u8 *)0x04000245 = 0x92;
    case 16:
        *(volatile u8 *)0x04000244 = 0x82;
        break;
    case 80:
        *(volatile u8 *)0x04000246 = 0x92;
        *(volatile u8 *)0x04000244 = 0x82;
        break;
    case 96:
        *(volatile u8 *)0x04000246 = 0x8a;
    case 32:
        *(volatile u8 *)0x04000245 = 0x82;
        break;
    case 64:
        *(volatile u8 *)0x04000246 = 0x82;
        break;
    default:
        break;
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
