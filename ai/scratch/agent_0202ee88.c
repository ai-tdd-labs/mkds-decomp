// PURPOSE: Updates the selected active entry from the latest timing change.
// The shared state selects one 64-byte entry.
// Inactive entries are left unchanged.

#pragma optimize_for_size on

typedef struct Entry {
    int active;
    char pad_04[2];
    unsigned short value;
    char pad_08[0x38];
} Entry;

typedef struct WorkState {
    char pad_00[8];
    Entry *entries;
    char pad_0c[0x22];
    unsigned short selected_entry;
    int multiplier;
    int divisor_base;
    char pad_38[8];
    int current_value;
    int previous_value;
} WorkState;

extern WorkState *data_02174e48;
extern int _s32_div_f(int dividend, int divisor);

void func_0202ee88(void)
{
    register const Entry *entries;
    register int entry_offset;

    entry_offset = ((volatile WorkState *)data_02174e48)->selected_entry << 6;
    entries = data_02174e48->entries;

    if (*(const int *)((const char *)entries + entry_offset) != 0) {
        *(unsigned short *)((char *)entries + entry_offset + 6) =
            _s32_div_f(
                data_02174e48->multiplier *
                    (data_02174e48->current_value -
                     data_02174e48->previous_value),
                data_02174e48->divisor_base - 5);
    }
}
