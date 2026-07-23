// PURPOSE: Updates the staff roll state and formats its text when needed.
//
// This probably advances the current linked staff-roll state from its next
// value.  State 1 rebuilds the displayed BMG text; states 0 and 2 do nothing.

typedef struct StaffRollData {
    int f0;
    int f4;
} StaffRollData;

extern StaffRollData *data_0217d40c;
extern void FormatSomeStaffRollBmgString(void);

void func_0212b204(void)
{
    data_0217d40c->f0 = data_0217d40c->f4;

    if (data_0217d40c->f0 == 0) {
        return;
    }

    if (data_0217d40c->f0 == 1) {
        FormatSomeStaffRollBmgString();
    } else if (data_0217d40c->f0 == 2) {
        return;
    }
}
