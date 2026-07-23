// PURPOSE: Initializes the graphics hardware for rendering.
// This configures both display engines and resets their background state.
// It also acquires the graphics VRAM lock and clears hardware registers.

typedef signed int s32;
typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 data_021802a8;
extern u32 data_0216f074;

extern void Gfx_InitializeState(void);
extern s32 Os_AllocateLockId(void);
extern void Os_Terminate(void);
extern void Mem_DmaFill32(u32 dmaNo, void *destination, u32 value, u32 size);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

void Gfx_Initialize(void)
{
    *(volatile u16 *)0x04000304 |= 0x8000;
    *(volatile u16 *)0x04000304 =
        (u16)((*(volatile u16 *)0x04000304 & ~0x020e) | 0x020e);
    *(volatile u16 *)0x04000304 =
        (u16)(*(volatile u16 *)0x04000304 | 1);

    Gfx_InitializeState();

    s32 lockId;
    while (data_021802a8 == 0) {
        lockId = Os_AllocateLockId();
        if (lockId == -3) {
            Os_Terminate();
        }
        data_021802a8 = (u16)lockId;
    }

    *(volatile u16 *)0x04000004 = 0;
    *(volatile u32 *)0x04000000 = 0;

    if (data_0216f074 != (u32)-1) {
        Mem_DmaFill32(data_0216f074, (void *)0x04000008, 0, 0x60);
        *(volatile u16 *)0x0400006c = 0;
        Mem_DmaFill32(data_0216f074, (void *)0x04001000, 0, 0x70);
    } else {
        MIi_CpuClear32(0, (void *)0x04000008, 0x60);
        *(volatile u16 *)0x0400006c = 0;
        MIi_CpuClear32(0, (void *)0x04001000, 0x70);
    }

    *(volatile u16 *)0x04000020 = 0x100;
    *(volatile u16 *)0x04000026 = 0x100;
    *(volatile u16 *)0x04000030 = 0x100;
    *(volatile u16 *)0x04000036 = 0x100;
    *(volatile u16 *)0x04001020 = 0x100;
    *(volatile u16 *)0x04001026 = 0x100;
    *(volatile u16 *)0x04001030 = 0x100;
    *(volatile u16 *)0x04001036 = 0x100;
}
