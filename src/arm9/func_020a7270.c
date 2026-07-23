/*
 * PURPOSE: Removes a balloon/shine from a driver and applies the loss effect.
 *
 * Arguments: a1 - pointer to a race/driver context object.
 * Behaviour: bails out immediately if func_020a1154 (probably "does this
 * driver still have a balloon/shine to lose?") reports false. Otherwise it
 * decrements the driver's balloon/shine count and forwards both the driver
 * and its own driver entry to func_020a5608 (probably an item-loss/pop
 * effect handler), which is called with the same driver entry twice.
 */

extern int func_020a1154(void *a1);
extern void MaybeUpdateDriverBalloonShineCount(void *a1, int delta);
extern void *GetDriverEntry(void *a1);
extern void func_020a5608(void *driverEntry1, void *driverEntry2);

void func_020a7270(void *a1)
{
    if (!func_020a1154(a1)) {
        return;
    }

    MaybeUpdateDriverBalloonShineCount(a1, -1);

    func_020a5608(GetDriverEntry(a1), GetDriverEntry(a1));
}
