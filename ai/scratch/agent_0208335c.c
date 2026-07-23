// PURPOSE: Updates a racer's sampled pose and status for the current frame.
// A nonzero second argument skips the update.
// The selected racer entry supplies rotation and position samples.
// Status bits track whether sampling is active and whether ten ticks elapsed.

typedef int fx32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} VecFx32;

typedef struct MQRacerEntry {
    u8 pad74[0x74];
    u16 f74;
    u8 pad2a4[0x2a4 - 0x76];
    fx32 f2a4;
} MQRacerEntry;

typedef struct MQRacerObject {
    u8 pad20[0x20];
    VecFx32 **f20;
    struct {
        u32 b0 : 1;
        u32 b1 : 1;
        u32 rest : 30;
    } f24;
    fx32 f28;
    fx32 f2c;
    fx32 f30;
    u8 pad50[0x50 - 0x34];
    u16 f50;
    u16 f52;
    u16 f54;
    u8 pad94[0x94 - 0x56];
    MQRacerEntry *f94;
    u8 pad99[0x99 - 0x98];
    u8 f99;
    u8 f9a;
    u8 f9b;
} MQRacerObject;

extern int StructMQRacerEntry_SomeFn_51(MQRacerEntry *racer, int racerIndex,
                                         void *entryBase);
extern u8 *data_0217ae84;

void func_0208335c(void *object, int skip)
{
    int active;
    MQRacerObject *obj;
    MQRacerEntry *racer;
    u32 counter;
    u8 *entry;
    int counterEnabled;
    int sampleIndex;
    u8 *entryBase;
    u16 *rotation;
    fx32 *position;

    if (skip != 0)
        return;

    obj = (MQRacerObject *)object;
    racer = obj->f94;
    entryBase = data_0217ae84;
    entry = entryBase + (u32)racer->f74 * 0x58;

    counter = obj->f9a;
    counterEnabled = obj->f99;
    sampleIndex = obj->f9b;
    active = 1;
    if (StructMQRacerEntry_SomeFn_51(racer, racer->f74, entryBase) == 0) {
        if (racer->f2a4 >= 0x119a)
            active = 0;
    }
    obj->f24.b1 = active != 0;

    if (counterEnabled != 0) {
        counter = (counter + 1) & 0xff;
        if (counter == 10)
            obj->f24.b0 = 1;
    }

    rotation = (u16 *)(entry + sampleIndex * 6);
    obj->f9a = (u8)counter;
    obj->f50 = *(u16 *)((u8 *)rotation + 0x4c);
    obj->f52 = *(u16 *)((u8 *)rotation + 0x4e);
    position = (fx32 *)(entry + sampleIndex * 12);
    obj->f54 = *(u16 *)((u8 *)rotation + 0x50);

    obj->f28 = *(fx32 *)((u8 *)position + 0x34) + (*obj->f20)->y;
    obj->f2c = *(fx32 *)((u8 *)position + 0x38) + (*obj->f20)->z;
    obj->f30 = *(fx32 *)((u8 *)position + 0x3c) + (*obj->f20)->w;
}
