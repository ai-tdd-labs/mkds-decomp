// PURPOSE: Initializes the 3D graphics state for the game.
extern void G3X_Initialize(void);
extern void func_02011074(void);

void func_02012f24(void)
{
    G3X_Initialize();
    func_02011074();
    *(volatile unsigned int *)0x04000600 =
        (*(volatile unsigned int *)0x04000600 & ~0xc0000000) | 0x80000000;
}
