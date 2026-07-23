// PURPOSE: Initializes the shared multiplayer work buffers.
// The memory argument supplies storage for two aligned work areas.
// The list is copied into both areas, while the other arguments configure the main area.
// An already-active shared area makes the function return 2 without rebuilding it.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SetupList {
    u8 unk_00;
    u8 count;
    u16 entries[10];
} SetupList;

extern u16 data_0216fda0;
extern u8 *data_0216fda8;
extern u8 *data_0216fdac;
extern u16 *data_021617a0;

extern int func_02142eac(void);
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern int func_0200a184(void);

int SetupSomePointer_from_thumb(void *memory, SetupList *list, u32 owner,
                                int value, int mode)
{
    u32 irqState;
    volatile u16 fillValue;
    volatile u32 clearValue;
    u8 *mainArea;
    u8 *sharedArea;
    int i;

    if (data_0216fdac != 0 &&
        *(u16 *)(data_0216fdac + 0x1316) != 0) {
        return 2;
    }

    mainArea = (u8 *)(((u32)memory + 0x1f) & ~0x1f);
    sharedArea = (u8 *)(((u32)mainArea + 0x1e1f) & ~0x1f);

    if (value == 0x10000) {
        value = func_02142eac();
    }

    irqState = Os_DisableIrq();

    data_0216fda0 = mode;
    data_0216fda8 = mainArea;
    data_0216fdac = sharedArea;

    clearValue = 0;
    MIi_CpuClear32(clearValue, mainArea, 0x1e00);

    fillValue = 0;
    Mem_CpuFill16(fillValue, sharedArea, 0x1340);

    for (i = 0; i < list->count; i++) {
        *(u16 *)(mainArea + 0x530 + ((u32)i << 1)) = list->entries[i];
    }

    for (i = 0; i < 16; i++) {
        u16 *entry = data_021617a0;

        if (*entry == 0) {
            break;
        }

        data_021617a0 = entry + 1;
        *(u16 *)(mainArea + 0x538 + ((u32)i << 1)) = *entry;
    }

    Mem_CpuCopy8(list, sharedArea + 0x1300, 0x16);

    if (list->count < 10) {
        *(u16 *)(sharedArea + 0x1302 + ((u32)list->count << 1)) = 0;
    }

    *(u16 *)(mainArea + 0x500) = 0x100;
    *(u16 *)(mainArea + 0x502) = 8;
    *(u16 *)(mainArea + 0x518) = 0;
    *(u16 *)(mainArea + 0x51a) = 0;
    *(u16 *)(mainArea + 0x52c) = 1;
    *(u32 *)(mainArea + 0x504) = (u32)(sharedArea + 0x400);
    *(u16 *)(mainArea + 0x0e) = 1;
    *(u16 *)(mainArea + 0x12) = 0;
    *(u16 *)(mainArea + 0x16) = 1;
    *(u16 *)(mainArea + 0x14) = 0;
    *(u32 *)(mainArea + 0x08) = owner;
    *(u16 *)(mainArea + 0x0c) = value;
    *(u16 *)(mainArea + 0x18) = func_0200a184() + 0xc8;
    *(u16 *)(mainArea + 0x10) = 0x0f;
    *(u8 *)(mainArea + 0x50c) = 0;
    *(u8 *)(mainArea + 0x50d) = 0;

    *(u16 *)(sharedArea + 0x1316) = 1;
    *(u32 *)(sharedArea + 0x131c) = 0;

    Os_RestoreIrq(irqState);
    return 0;
}
