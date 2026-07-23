// PURPOSE: Applies a short movement curve to a racer.
// The racer provides its driver index, state flags, and curve position.
// A special state uses another handler; otherwise three fixed-point tables
// probably scale the racer's movement until the curve finishes.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;
typedef long long fx64;

typedef struct RacerStatusEntry {
    u16 value;
    u8 pad_002[0x5c - 2];
} RacerStatusEntry;

typedef struct StructMQRacerEntry {
    u8 pad_000[0x78];
    int driverIndex;
    u32 flags;
    u8 pad_080[0xbc - 0x80];
    fx32 outputX;
    fx32 outputY;
    fx32 outputZ;
    u8 pad_0c8[0x3c8 - 0xc8];
    short adjustmentFrame;
    u8 pad_3ca[0x41c - 0x3ca];
    fx32 tableX;
    fx32 tableY;
    fx32 tableZ;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    fx32 extraYScale;
} StructMQRacerEntry;

extern void StructMQRacerEntry_SomeFn_53(StructMQRacerEntry *racer);

extern RacerStatusEntry data_0217566a[];
extern fx32 data_02154de4[];
extern fx32 data_02154e48[];
extern fx32 data_02154eac[];

void func_020732d8(StructMQRacerEntry *racer)
{
    int frame;

    data_0217566a[racer->driverIndex].value = 0xff7;

    if (racer->flags & 0x20) {
        StructMQRacerEntry_SomeFn_53(racer);
        return;
    }

    racer->adjustmentFrame++;
    frame = racer->adjustmentFrame;
    if (frame >= 0x19) {
        racer->flags &= ~0x80;
        return;
    }

    /* Keep one signed curve index for all three parallel table reads. */
    racer->tableX = data_02154de4[frame];
    racer->tableY = data_02154e48[frame];
    racer->tableZ = data_02154eac[frame];

    racer->outputX = (fx32)(((fx64)racer->scaleX * racer->tableX) >> 12);
    racer->outputY = (fx32)(((fx64)racer->scaleY * racer->tableY) >> 12);
    racer->outputZ = (fx32)(((fx64)racer->scaleZ * racer->tableZ) >> 12);
    racer->outputY = (fx32)(((fx64)racer->extraYScale * racer->outputY) >> 12);
}
