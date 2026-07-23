typedef unsigned short u16;
typedef unsigned int u32;

#define reg_GXS_DISPCNT (*(volatile u32 *)0x04001000)

void GXS_SetGraphicsMode__mkds_ceb54(u32 flags)
{
    u32 val = reg_GXS_DISPCNT;
    val &= ~0x1f00;
    reg_GXS_DISPCNT = val | (flags << 8);
}
