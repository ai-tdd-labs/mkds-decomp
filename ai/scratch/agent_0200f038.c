// PURPOSE: Computes the end address of a system memory region.
// The region selects main memory, extended memory, TCM, shared memory, or WRAM.
// Extended main memory is unavailable on unsupported console configurations.
// The DTCM result leaves room for the interrupt and system stacks.

typedef unsigned int u32;
typedef signed int s32;

extern int data_021701b8;
extern u32 Os_GetSystemFlags(void);

void *Os_ComputeMemoryRegionEndAddress(int region)
{
    switch (region) {
    case 0:
        return (void *)0x023e0000;

    case 2:
        if (!data_021701b8 ||
            (Os_GetSystemFlags() & 3) == 1) {
            return (void *)0;
        } else {
            return (void *)0x02700000;
        }

    case 3:
        return (void *)0x02000000;

    case 4:
    {
        u32 interruptStackBottom =
            (u32)(volatile unsigned char *)0x027e0000 + 0x3f80 -
            (s32)(void (*)(void))0x00000c00;
        u32 systemStackBottom;

        if (!(s32)(void (*)(void))0x00002800) {
            systemStackBottom =
                (u32)(volatile unsigned char *)0x027e0000;
            if (systemStackBottom <
                (u32)(volatile unsigned char *)0x027e00e0) {
                systemStackBottom =
                    (u32)(volatile unsigned char *)0x027e00e0;
            }
        } else if ((s32)(void (*)(void))0x00002800 < 0) {
            systemStackBottom =
                (u32)(volatile unsigned char *)0x027e00e0 -
                (s32)(void (*)(void))0x00002800;
        } else {
            systemStackBottom =
                interruptStackBottom -
                (s32)(void (*)(void))0x00002800;
        }
        return (void *)systemStackBottom;
    }

    case 5:
        return (void *)(volatile unsigned char *)0x027ff680;

    case 6:
        return (void *)0x037f8000;

    default:
        return (void *)0;
    }
}
