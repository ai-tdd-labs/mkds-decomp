// PURPOSE: Updates the racer entry when the driver is active.
// The driver context probably contains status flags and a racer entry pointer.
// It skips the update while either relevant status flag is set.

typedef unsigned int u32;

typedef struct DriverContext {
    u32 unknown00[0x48 / sizeof(u32)];
    u32 flags;
    u32 unknown4c[(0x3cc - 0x4c) / sizeof(u32)];
    void *racerEntry;
} DriverContext;

extern void StructMQRacerEntry_SomeFn_5(DriverContext *driver, void *entry, int value);

void DriverContext_SomeFn_0(DriverContext *driver) {
    if (driver->flags & 0x840) {
        return;
    }

    StructMQRacerEntry_SomeFn_5(driver, driver->racerEntry, 7);
}
