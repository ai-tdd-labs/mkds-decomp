/*
 * PURPOSE: Removes a balloon/shine from driver a1 and plays the loss effect against driver b (or a1 itself if b is out of range).
 *
 * Arguments: a1 - driver index that is losing a balloon/shine.
 *            b  - driver index of the "attacker"/target driver entry to pass
 *                 alongside a1's entry; if b is not a valid driver index
 *                 (>= 8), a1 is used instead.
 * Returns: 0 if func_020a1154(a1) reports the driver has nothing to lose
 * (no-op); otherwise decrements a1's balloon/shine count, forwards both
 * driver entries to func_020a5608 (item-loss/pop effect handler), and
 * returns 1.
 */

extern int func_020a1154(int a1);
extern void MaybeUpdateDriverBalloonShineCount(int a1, int delta);
extern void *GetDriverEntry(int idx);
extern void func_020a5608(void *driverEntry1, void *driverEntry2);

int func_020a72c8(int a1, int b)
{
    if (!func_020a1154(a1)) {
        goto fail;
    }

    MaybeUpdateDriverBalloonShineCount(a1, -1);

    if ((unsigned int)b >= 8) {
        b = a1;
    }

    func_020a5608(GetDriverEntry(a1), GetDriverEntry(b));

    return 1;

fail:
    return 0;
}
