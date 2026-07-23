// PURPOSE: Clears the per-player state of inactive race slots.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceState02058338 {
    u8 pad000[0x43c];
    u8 slotBits;
    u8 pad43d[0x162a - 0x43d];
    u8 activeSlots;
} RaceState02058338;

typedef struct ModeState02058338 {
    int unk0;
    int slotBits;
} ModeState02058338;

extern RaceState02058338 *data_0217aa00;
extern ModeState02058338 *data_021759d0;

extern void func_0214358c(int, void *, void *);
extern void Mem_CpuFill8(void *, int, unsigned int);

void func_02058338(void)
{
    u8 i;
    int one;

    func_0214358c(14, 0, 0);
    data_0217aa00->slotBits =
        *(volatile u8 *)((u8 *)data_0217aa00 + 0x684) >> 4;
    if (*(volatile u16 *)0x027ffc40 == 2) {
        data_021759d0->slotBits = data_0217aa00->slotBits;
    }

    one = 1;
    for (i = one; i < 8; i++) {
        if ((data_0217aa00->activeSlots & (one << i)) == 0) {
            Mem_CpuFill8((u8 *)data_0217aa00 + 0x45c + i * 0x22c,
                         0, 0x22c);
        }
    }
}
