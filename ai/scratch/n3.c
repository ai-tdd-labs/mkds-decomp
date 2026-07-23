typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define reg_GX_VRAMCNT     (*(volatile u32 *)0x04000240)
#define reg_GX_VRAMCNT_E   (*(volatile u8 *)0x04000244)
#define reg_GX_VRAMCNT_F   (*(volatile u8 *)0x04000245)
#define reg_GX_VRAMCNT_G   (*(volatile u8 *)0x04000246)
#define reg_GX_VRAM_HI_CNT (*(volatile u16 *)0x04000248)

struct GX_State
{
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
};

struct GX_State gGXState;

void Gfx_InitializeState(void)
{
    gGXState.lcdc = 0x0;
    gGXState.bg = 0x0;
    gGXState.obj = 0x0;
    gGXState.arm7 = 0x0;
    gGXState.tex = 0x0;
    gGXState.texPltt = 0x0;
    gGXState.clrImg = 0x0;
    gGXState.bgExtPltt = 0x0;
    gGXState.objExtPltt = 0x0;
    gGXState.sub_bg = 0x0;
    gGXState.sub_obj = 0x0;
    gGXState.sub_bgExtPltt = 0x0;
    gGXState.sub_objExtPltt = 0x0;
    reg_GX_VRAMCNT = 0x0;
    reg_GX_VRAMCNT_E = 0x0;
    reg_GX_VRAMCNT_F = 0x0;
    reg_GX_VRAMCNT_G = 0x0;
    reg_GX_VRAM_HI_CNT = 0x0;
}
