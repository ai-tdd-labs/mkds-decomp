/* PURPOSE: During the staff-roll/award sequence, mark a driver's slot in the
 * shared entry table as "state 10" once its driver-entry lookup succeeds.
 */

typedef struct {
    char pad[0x64];
    int f64;
    char pad2[0x70 - 0x64 - 4];
} SlotEntry;

extern int IsAwardOrStaffRoll(void);
extern void *GetDriverEntry(int a);
extern int func_01ffc67c(void *entry);
extern SlotEntry *data_0217b1fc;

void func_020a22ac(int a)
{
    if (IsAwardOrStaffRoll() != 1)
        return;

    if (func_01ffc67c(GetDriverEntry(a)) != 0)
        return;

    data_0217b1fc[a].f64 = 10;
}
