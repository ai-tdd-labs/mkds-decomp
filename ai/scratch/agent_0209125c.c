/*
 * PURPOSE: Registers a pair of task callback functions (main + exit) with
 * an unknown low-level task/thread-creation routine.
 * Passes fixed constants (0, 0, 1, 0x161) alongside the two function
 * pointers; the exact meaning of the numeric args is unknown (probably
 * a priority/stack-size-like pair), but they are literal pool constants
 * with no relocation, so they must stay as plain integer literals.
 */

extern void func_02091828(void);
extern void func_020917d0(void);
extern void func_0209bf70(void *a0, void *a1, int a2, int a3, int a4, int a5);

void func_0209125c(void)
{
    func_0209bf70(func_02091828, func_020917d0, 0, 0, 1, 0x161);
}
