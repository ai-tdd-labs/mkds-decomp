// PURPOSE: Resets the wireless session state before a new connection starts.
// The argument is probably a per-session workspace containing eight packet buffers.
// This also clears related status flags and bookkeeping in the shared wireless context.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct WirelessSharedState {
    u16 rows[8][4];
    u8 pad_040[0x60 - 0x40];
    u8 field_60;
    u8 pad_061[0x68 - 0x61];
    u8 field_68;
} WirelessSharedState;

typedef struct WirelessContext {
    u8 pad_000[0x8b];
    u8 flags_08b;
    u8 pad_08c[0x454 - 0x08c];
    u16 flags_454;
    u8 pad_456[0x15c4 - 0x456];
    void *buffer_15c4;
    u8 pad_15c8[0x1e4c - 0x15c8];
    WirelessSharedState shared_1e4c;
} WirelessContext;

typedef struct WirelessSessionWork {
    u8 pad_000[0x0c];
    u8 *buffer_00c;
    u32 slots_010[8];
    u8 field_030;
    u8 pad_031[3];
    u32 field_034;
    u16 field_038;
    u8 field_03a;
    u8 pad_03b;
    u16 field_03c;
    u8 pad_03e[0x4a - 0x3e];
    u8 field_04a;
} WirelessSessionWork;

extern WirelessContext *data_0217aa00;
extern void Mem_CpuFill8(void *destination, int value, u32 size);

void func_02054208(WirelessSessionWork *work)
{
    WirelessSharedState *shared;
    int i;
    int j;

    work->field_03a = 0;
    Mem_CpuFill8(data_0217aa00->buffer_15c4, 0, 8);

    for (i = 0; i < 8; i++) {
        work->slots_010[i] = 0;
        Mem_CpuFill8(work->buffer_00c + i * 8, 0, 8);
    }

    work->field_03c = 0;
    for (i = 0; i < 7; i++) {
        ((u16 *)((u8 *)work + 0x3c))[i] = 0;
    }

    work->field_04a = 0;
    work->field_034 = 5;
    work->field_038 = 0;
    work->field_030 = 0;

    data_0217aa00->flags_454 &= ~0x10;
    data_0217aa00->flags_08b &= ~1;

    shared = &data_0217aa00->shared_1e4c;
    shared->field_60 = 0;
    shared->field_68 = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 3; j++) {
            shared->rows[i][j] = 0;
        }
    }

    data_0217aa00->flags_454 &= ~0x10;
}
