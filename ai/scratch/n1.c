typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define reg_GX_VRAMCNT_A (*(volatile u8 *)0x04000240)
#define reg_GX_VRAMCNT_B (*(volatile u8 *)0x04000241)
#define reg_GX_VRAMCNT_C (*(volatile u8 *)0x04000242)
#define reg_GX_VRAMCNT_D (*(volatile u8 *)0x04000243)
#define reg_GX_VRAMCNT_E (*(volatile u8 *)0x04000244)
#define reg_GX_VRAMCNT_F (*(volatile u8 *)0x04000245)
#define reg_GX_VRAMCNT_G (*(volatile u8 *)0x04000246)
#define reg_GX_VRAMCNT_H (*(volatile u8 *)0x04000248)
#define reg_GX_VRAMCNT_I (*(volatile u8 *)0x04000249)

void GX_VRAMCNT_SetLCDC_(u32 mask) {
    if (mask & (0x1 << 0))
        reg_GX_VRAMCNT_A = 0x80;
    if (mask & (0x1 << 1))
        reg_GX_VRAMCNT_B = 0x80;
    if (mask & (0x1 << 2))
        reg_GX_VRAMCNT_C = 0x80;
    if (mask & (0x1 << 3))
        reg_GX_VRAMCNT_D = 0x80;
    if (mask & (0x1 << 4))
        reg_GX_VRAMCNT_E = 0x80;
    if (mask & (0x1 << 5))
        reg_GX_VRAMCNT_F = 0x80;
    if (mask & (0x1 << 6))
        reg_GX_VRAMCNT_G = 0x80;
    if (mask & (0x1 << 7))
        reg_GX_VRAMCNT_H = 0x80;
    if (mask & (0x1 << 8))
        reg_GX_VRAMCNT_I = 0x80;
}
