// PURPOSE: Updates an object's light data from its racer state.
// The first argument supplies the object whose racer state is used.
// The second argument receives the updated light data and may have a flag set.
// The selected second vector probably depends on the racer's mode bit.

typedef struct Vec3i {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct LightInfo {
    unsigned short value[9];
} LightInfo;

typedef struct RacerState {
    unsigned char pad_000[0x48];
    int flags;
    unsigned char pad_04c[0x110];
    Vec3i fallbackVector;
    unsigned char pad_168[0x488];
    LightInfo *lightInfo;
} RacerState;

typedef struct Object {
    unsigned char pad_000[0x1fc];
    RacerState *racer;
} Object;

typedef struct Output {
    unsigned char pad_000[0x74];
    unsigned int flags;
} Output;

extern LightInfo data_021595d8;
extern LightInfo *StructMQRacerEntry_SomeFn_71(RacerState *racer);
extern void func_020f98a0(Output *object, const Vec3i *first,
                           const Vec3i *second, const LightInfo *lightInfo,
                           int hasMode);

void func_020efd1c(Object *object, Output *output)
{
    RacerState *racer = object->racer;
    Vec3i *second;
    volatile LightInfo *lightInfo = StructMQRacerEntry_SomeFn_71(racer);

    if (racer->flags & 1) {
        second = (Vec3i *)((unsigned char *)racer + 0x15c);
    } else {
        second = (Vec3i *)&data_021595d8;
    }

    func_020f98a0(output, (Vec3i *)((unsigned char *)racer + 0x98), second,
                  (LightInfo *)((unsigned char *)racer->lightInfo + 0x40),
                  (int)lightInfo);

    if (racer->flags & 1) {
        output->flags |= 0x40000000;
    }
}
