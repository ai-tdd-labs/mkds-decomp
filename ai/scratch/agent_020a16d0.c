/*
 * PURPOSE: Runs the direct "maybe kill driver" check for one racer slot,
 * unless the race is already over or that racer already has a result.
 *
 * arg0 (r0) is a racer index. data_0217b1fc holds a pointer to the shared
 * race-manager struct; +0x3b4 is probably a "race finished" flag/count and
 * is checked first (early-out if nonzero). The racer array itself starts at
 * the same base pointer, stride 0x70 bytes per racer; +8 of a racer entry is
 * probably a "result/rank already set" flag (early-out if nonzero).
 * Otherwise calls MaybeKillDriverDirect(idx) then func_020a1790(idx).
 */

extern int data_0217b1fc;

extern void MaybeKillDriverDirect(int idx);
extern void func_020a1790(void);

void func_020a16d0(int idx)
{
    char *base = *(char **)&data_0217b1fc;

    if (*(int *)(base + 0x3b4) >= 0)
    {
        return;
    }

    if (*(int *)(base + idx * 0x70 + 8) != 0)
    {
        return;
    }

    MaybeKillDriverDirect(idx);
    func_020a1790();
}
