// PURPOSE: Resets the 3D projection and position-vector matrix stacks.
// Waits for both matrix-stack level commands to finish.
// It then restores the projection and position-vector stacks through the 3D hardware registers.

typedef unsigned int u32;

extern int G3X_GetMtxStackLevelPV(int *level);
extern int G3X_GetMtxStackLevelPJ(int *level);

void G3X_ResetMatrixStack2(void)
{
    int levelPV;
    int levelPJ;

    *(volatile u32 *)0x04000600 |= 0x8000;

    while (G3X_GetMtxStackLevelPV(&levelPV) != 0) {
    }

    while (G3X_GetMtxStackLevelPJ(&levelPJ) != 0) {
    }

    *(volatile u32 *)0x04000440 = 3;
    *(volatile u32 *)0x04000454 = 0;
    *(volatile u32 *)0x04000440 = 0;

    if (levelPJ != 0) {
        *(volatile u32 *)0x04000448 = levelPJ;
    }

    *(volatile u32 *)0x04000440 = 2;
    *(volatile u32 *)0x04000448 = levelPV;
    *(volatile u32 *)0x04000454 = 0;
}
