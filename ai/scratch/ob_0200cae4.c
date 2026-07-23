typedef unsigned short u16;
typedef unsigned int u32;

#define reg_OS_IME (*(volatile u16 *)0x04000208)
#define reg_OS_IE  (*(volatile u32 *)0x04000210)

u32 Os_EnableIrqHandler(u32 mask)
{
    u16 regIme = reg_OS_IME;
    reg_OS_IME = 0;
    u32 regIe = reg_OS_IE;
    reg_OS_IE = regIe | mask;
    u16 unused = reg_OS_IME;
    reg_OS_IME = regIme;
    return regIe;
}
