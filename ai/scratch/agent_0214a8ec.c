// PURPOSE: Initializes the 3D matrix stacks.
// Waits until both hardware matrix-stack commands finish.
// It resets the projection and position-vector stacks through the 3D registers.
// The hardware command writes probably use their values only as FIFO triggers.

typedef unsigned int u32;

extern int G3X_GetMtxStackLevelPV(int *level);
extern int G3X_GetMtxStackLevelPJ(int *level);

void G3X_InitializeMatrixStack(void)
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

    *(volatile u32 *)0x04000440 = 0;
    *(volatile u32 *)0x04000440 = 2;
    *(volatile u32 *)0x04000448 = levelPV;
    *(volatile u32 *)0x04000448 = 0;
}
