typedef unsigned int u32;

#define reg_GXS_DISPCNT (*(volatile u32 *)0x04001000)

void GXS_SetGraphicsMode__mkds_3038c(u32 mode)
{
    u32 val = reg_GXS_DISPCNT;
    val &= ~0xe000;
    reg_GXS_DISPCNT = val | (mode << 13);
}
