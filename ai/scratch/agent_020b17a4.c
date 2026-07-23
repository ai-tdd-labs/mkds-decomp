// PURPOSE: Configures the sub screen backgrounds for a layered menu display.
// This sets the sub display mode and initializes backgrounds 1 through 3.
// It also resets the horizontal offsets for backgrounds 1 through 3.

typedef unsigned short u16;
typedef unsigned int u32;

extern void SetDispcntSubBgMode(u32 mode);

void func_020b17a4(void)
{
    *(volatile u32 *)0x04001000 =
        (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x1e00;
    SetDispcntSubBgMode(0);

    *(volatile u32 *)0x04001014 = 0;

    *(volatile u16 *)0x0400100a =
        (*(volatile u16 *)0x0400100a & ~3) | 3;
    *(volatile u16 *)0x0400100a &= ~0x40;
    *(volatile u16 *)0x0400100a =
        (*(volatile u16 *)0x0400100a & 0x43) | 8;
    *(volatile u32 *)0x04001018 = 0x100;

    *(volatile u16 *)0x0400100c =
        (*(volatile u16 *)0x0400100c & ~3) | 2;
    *(volatile u16 *)0x0400100c &= ~0x40;
    *(volatile u16 *)0x0400100c =
        (*(volatile u16 *)0x0400100c & 0x43) | 0x4c08;
    *(volatile u32 *)0x0400101c = 0x100;

    *(volatile u16 *)0x0400100e =
        (*(volatile u16 *)0x0400100e & ~3) | 2;
    *(volatile u16 *)0x0400100e &= ~0x40;
    *(volatile u16 *)0x0400100e =
        (*(volatile u16 *)0x0400100e & 0x43) | 0x4e08;
}
