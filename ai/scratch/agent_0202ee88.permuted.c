// PURPOSE: Updates the active selected entry using a scaled timing delta.

#pragma optimize_for_size on

typedef struct Entry {
    int active;
    char _04[2];
    unsigned short value;
    char _08[0x38];
} Entry;

typedef struct WorkState {
    char _00[8];
    Entry *entries;
    char _0C[0x22];
    unsigned short selected_entry;
    int multiplier;
    int divisor_base;
    char _38[8];
    int current_value;
    int previous_value;
} WorkState;

extern WorkState *data_02174e48;
extern int _s32_div_f(int dividend, int divisor);

void func_0202ee88(void)
{
    register const Entry *entries;
    register unsigned short selected_entry;

    selected_entry = ((volatile WorkState *)data_02174e48)->selected_entry;
    entries = (Entry *)(char *)data_02174e48->entries;
    if (entries[selected_entry].active != 0) {
        ((Entry *)entries)[selected_entry].value =
            _s32_div_f((data_02174e48->current_value - data_02174e48->previous_value) * data_02174e48->multiplier,
                data_02174e48->divisor_base - 5);
    }
}
