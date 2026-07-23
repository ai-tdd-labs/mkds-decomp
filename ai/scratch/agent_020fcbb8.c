// PURPOSE: Checks whether a racer is close enough to interact with an object.
// The object and driver index select the positions and state to compare.
// It records the racer and its position when all distance and flag checks pass.

typedef unsigned char u8;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct DriverEntry {
    u8 padding_000[0x48];
    unsigned int flags_048;
    u8 padding_04c[0x4c];
    VecFx32 position_098;
} DriverEntry;

typedef struct RacerSlot {
    u8 padding_000[0x1f0];
    void *object_1f0;
    u8 padding_1f4[0x1c];
} RacerSlot;

typedef struct Object {
    u8 padding_000[0x50];
    VecFx32 position_050;
    u8 padding_05c[0x18];
    unsigned int flags_074;
    u8 padding_078[0x78];
    VecFx32 direction_0f0;
    u8 padding_0fc[0x6c];
    void *identity_168;
    u8 padding_16c[0xbc];
    RacerSlot *racer_228;
    u8 padding_22c[0x18];
    VecFx32 racer_position_244;
} Object;

extern DriverEntry *GetDriverEntry(int index);
extern int StructMQRacerEntry_SomeFn_64(DriverEntry *driver);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern int VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);

int func_020fcbb8(Object *object, int driverIndex)
{
    DriverEntry *driver;
    RacerSlot *racer;
    VecFx32 difference;
    VecFx32 *driverPosition;
    int useShortRange;
    int deltaX;
    int deltaZ;
    int cross;

    driver = GetDriverEntry(driverIndex);
    if (StructMQRacerEntry_SomeFn_64(driver) != 0) {
        return 0;
    }

    racer = (RacerSlot *)(*(u8 * volatile *)0x027e00c8 +
                          driverIndex * 0x210);
    driverPosition = &driver->position_098;

    if (racer->object_1f0 != object->identity_168) {
        if ((object->flags_074 & 0x40000000) != 0 ||
            (driver->flags_048 & 1) != 0) {
            useShortRange = 1;
        } else {
            useShortRange = 0;
        }

        VecFx32_Subtract(driverPosition, &object->position_050, &difference);
        deltaX = *(volatile int *)&difference.x;
        deltaZ = *(volatile int *)&difference.z;
        if ((deltaX >> 12) * (deltaX >> 12) +
                (deltaZ >> 12) * (deltaZ >> 12) >
            (useShortRange ? 40000 : 160000)) {
            return 0;
        }

        cross = VecFx32_CrossProduct_0(&object->direction_0f0, &difference);
        cross >>= 12;
        if (cross * cross > 2500) {
            return 0;
        }
    }

    if ((object->flags_074 & 0x10000000) != 0) {
        return 0;
    }

    object->racer_228 = racer;
    object->racer_position_244 = *driverPosition;
    return 1;
}
