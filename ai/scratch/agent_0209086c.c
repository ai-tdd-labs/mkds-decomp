/* PURPOSE: Sets up a kart object's driver state at the start of a race.
 *
 * obj  - the kart/object being initialized.
 * id   - the driver id/slot index, stored into obj+0x24.
 *
 * Looks up the driver record for id, then calls func_0207ffa4 with a
 * per-id config value read from a global driver-config array (element
 * stride 0x210, field at offset 0x1f0). Clears three fields on obj/driver
 * (obj+0x26, obj+0x28, driver+0x388), then applies the drift-boost setup
 * on the driver record.
 */

typedef unsigned char u8;

extern void *GetDriverEntry(int idx);
extern void func_0207ffa4(void *obj, int id, int cfgVal);
extern void DriverContext_ApplyDriftBoost(void *driver);

void func_0209086c(void *obj, int id)
{
    void *driver = GetDriverEntry(id);

    *(short *)((u8 *)obj + 0x24) = (short)id;

    /* global driver-config array base, no symbol at this dtcm address */
    u8 *cfgBase = *(u8 **)0x027e00c8;
    int cfgVal = *(int *)(cfgBase + id * 0x210 + 0x1f0);

    func_0207ffa4(obj, id, cfgVal);

    *(short *)((u8 *)obj + 0x26) = 0;
    *(short *)((u8 *)obj + 0x28) = 0;
    *(short *)((u8 *)driver + 0x388) = 0;

    DriverContext_ApplyDriftBoost(driver);
}
