// PURPOSE: Maps VRAM banks into texture memory.
// The bank mask is saved in the shared graphics state.
// Selected banks leave LCDC mode and receive texture-memory slots.

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

void func_021495e4(s32 tex)
{
    data_021802b0.lcdc =
        (u16)(~tex & (data_021802b0.lcdc | data_021802b0.tex));
    data_021802b0.tex = (u16)tex;

    if (tex == 0) {
        *(volatile u16 *)0x04000060 &= 0x0000cffe;
    } else {
        *(volatile u16 *)0x04000060 =
            (u16)((*(volatile u16 *)0x04000060 & ~0x3000) | 1);

        switch (tex) {
        case 5:
            *(volatile u8 *)0x04000240 = 0x83;
            *(volatile u8 *)0x04000242 = 0x8b;
            break;
        case 9:
            *(volatile u8 *)0x04000240 = 0x83;
            *(volatile u8 *)0x04000243 = 0x8b;
            break;
        case 10:
            *(volatile u8 *)0x04000241 = 0x83;
            *(volatile u8 *)0x04000243 = 0x8b;
            break;
        case 11:
            *(volatile u8 *)0x04000240 = 0x83;
            *(volatile u8 *)0x04000241 = 0x8b;
            *(volatile u8 *)0x04000243 = 0x93;
            break;
        case 13:
            *(volatile u8 *)0x04000240 = 0x83;
            *(volatile u8 *)0x04000242 = 0x8b;
            *(volatile u8 *)0x04000243 = 0x93;
            break;
        case 8:
            *(volatile u8 *)0x04000243 = 0x83;
            break;
        case 12:
            *(volatile u8 *)0x04000243 = 0x8b;
        case 4:
            *(volatile u8 *)0x04000242 = 0x83;
            break;
        case 14:
            *(volatile u8 *)0x04000243 = 0x93;
        case 6:
            *(volatile u8 *)0x04000242 = 0x8b;
        case 2:
            *(volatile u8 *)0x04000241 = 0x83;
            break;
        case 15:
            *(volatile u8 *)0x04000243 = 0x9b;
        case 7:
            *(volatile u8 *)0x04000242 = 0x93;
        case 3:
            *(volatile u8 *)0x04000241 = 0x8b;
        case 1:
            *(volatile u8 *)0x04000240 = 0x83;
            break;
        }
    }

    GX_VRAMCNT_SetLCDC_(data_021802b0.lcdc);
}
