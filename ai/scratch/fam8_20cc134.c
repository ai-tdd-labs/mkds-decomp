typedef unsigned short u16;
typedef unsigned int u32;

#define reg_GXS_DISPCNT (*(volatile u32 *)0x04001000)

void SetDispcntWindows01ObjDisplayFlagsSub(u32 flags)
{
    u32 val = reg_GXS_DISPCNT;
    val &= ~0xe000;
    reg_GXS_DISPCNT = val | (flags << 13);
}
