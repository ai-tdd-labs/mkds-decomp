// PURPOSE: Creates the two race-start sprites used by the battle-mode display.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad_00[0x18];
    int field_18;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern int GetB3C4_Cell_RaceStartBattleM(int mode);
extern int MaybeMakeOamSlot(void *slot, u16 position, int cell, int unused,
                            int *attributes, int unused2, int enabled);

void func_020d1198(void *work)
{
    int attributes_a[2];
    int attributes_b[2];
    int delta;
    int cell;

    *(volatile u32 *)0x04000000 &= ~0xe000;

    cell = GetB3C4_Cell_RaceStartBattleM(
        (gRaceConfig->field_18 == 0) ? 0 : 1);
    attributes_a[0] = 0x80000;
    attributes_a[1] = 0x60000;
    delta = MaybeMakeOamSlot(
        (char *)work + *(u16 *)((char *)work + 0x400) * 8,
        (u16)(0x80 - *(u16 *)((char *)work + 0x400)),
        cell,
        0,
        attributes_a,
        0,
        1);
    *(u16 *)((char *)work + 0x400) += delta;

    cell = GetB3C4_Cell_RaceStartBattleM(2);
    attributes_b[0] = 0x80000;
    attributes_b[1] = 0x60000;
    delta = MaybeMakeOamSlot(
        (char *)work + *(u16 *)((char *)work + 0x400) * 8,
        (u16)(0x80 - *(u16 *)((char *)work + 0x400)),
        cell,
        0,
        attributes_b,
        0,
        1);
    *(u16 *)((char *)work + 0x400) += delta;
}
