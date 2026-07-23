/*
 * PURPOSE: Copies a racer's low-byte status flag into that racer's kart-work
 *          slot, but only while the race hasn't finished and a few guard
 *          conditions on the racer's driver entry hold.
 *
 * Args: driverId = index of the racer (r0). entry = pointer to that racer's
 * driver-entry struct (r1), used directly (not fetched via GetDriverEntry).
 *
 * Bails out early (does nothing) if:
 *  - data_0217b1fc->field_3b4 is already >= 0 (race already past this point),
 *  - GetDriverEntry(driverId)->field_180 is 0 (driver slot not active),
 *  - entry->state is not 0, 1 or 9 (racer not in one of the expected states),
 *  - entry->field_78 has bit 0x8000 set (some "skip" flag).
 *
 * Otherwise it writes the low byte of entry->field_78 (top byte forced to 0)
 * into the driverId-th slot of the global kart-work array (data_0217b1fc),
 * at offset 0x44 (u16 field).
 */

typedef unsigned short u16;

typedef struct {
    char pad_00[0x3b4];
    int field_3b4;       /* offset 0x3b4: header field past the driver array */
} RaceWork;

typedef struct {
    char pad_00[0x180];
    int field_180;
} DriverEntry;

typedef struct {
    char pad_00[0x44];
    int state;          /* offset 0x44: expected 0, 1 or 9 */
    char pad_48[0x78 - 0x48];
    u16 field_78;        /* offset 0x78: bit 0x8000 = skip */
} Entry;

typedef struct {
    char pad_00[0x44];
    u16 f44;             /* offset 0x44: low byte of entry->field_78 */
    char pad_46[0x70 - 0x46];
} KartWork;

extern DriverEntry *GetDriverEntry(int id);
extern RaceWork *data_0217b1fc;

void func_020a1e40(int driverId, Entry *entry)
{
    DriverEntry *drv;
    int state;
    u16 flags78;
    KartWork *kw;

    if (data_0217b1fc->field_3b4 >= 0)
        return;

    drv = GetDriverEntry(driverId);
    if (drv->field_180 == 0)
        return;

    state = entry->state;
    if (state != 0 && state != 1 && state != 9)
        return;

    flags78 = entry->field_78;
    if (flags78 & 0x8000)
        return;

    kw = &((KartWork *)data_0217b1fc)[driverId];
    kw->f44 = flags78 & ~(u16)0xff00;
}
