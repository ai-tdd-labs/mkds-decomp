// PURPOSE: Records award-race conditions for the active driver.
// The race state supplies the driver and its driver-record index.
// Ineligible drivers leave the recorded flags unchanged and return zero.
// Eligible drivers add the applicable race and driver flags and return one.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Driver {
    u8 pad_000[0x4c];
    u32 flags_04c;
    u8 pad_050[0x180 - 0x50];
    int state_180;
} Driver;

typedef struct RaceState {
    int field_000;
    u8 pad_004[0x30 - 0x04];
    int field_030;
    u8 pad_034[0x58 - 0x34];
    int field_058;
    u8 pad_05c[0x1ec - 0x5c];
    u16 flags_1ec;
    u8 pad_1ee[0x1fc - 0x1ee];
    Driver *driver_1fc;
    int driver_entry_200;
} RaceState;

extern int IsAwardOrStaffRoll(void);

extern u16 data_021595b8;
extern u16 data_021595bc;
extern u16 data_021595c0;
extern u8 data_0217562a[];
extern u16 data_021595c4;
extern u16 data_021595c8;

int func_020f0154(RaceState *race)
{
    Driver *driver = race->driver_1fc;

    if (IsAwardOrStaffRoll() == 0) {
        return 0;
    }
    if (driver->state_180 != 0) {
        return 0;
    }
    if ((driver->flags_04c & 0x20000000) != 0) {
        return 0;
    }

    if (race->field_058 != 15) {
        race->flags_1ec |= data_021595b8;
    } else if (race->field_030 != 19) {
        race->flags_1ec |= data_021595bc;
    } else if (race->field_000 != 0) {
        race->flags_1ec |= data_021595c0;
    }

    if ((u16)(*(u16 *)(data_0217562a +
                       race->driver_entry_200 * 0x5c) &
              0x40) != 0) {
        race->flags_1ec |= data_021595c4;
    }

    if ((u16)(*(u16 *)(data_0217562a +
                       race->driver_entry_200 * 0x5c) &
              0x80) != 0) {
        race->flags_1ec |= data_021595c8;
    }

    return 1;
}
