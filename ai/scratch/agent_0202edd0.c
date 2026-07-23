// PURPOSE: Copies a selected entry value into the current entry.
// The shared work state owns the entry table and both selection indices.
// The helper probably returns an offset from the stored source index.

#pragma optimize_for_size on

typedef struct Entry {
    char pad_00[0x0e];
    short value;
    char pad_10[0x30];
} Entry;

typedef struct WorkState {
    char pad_00[4];
    unsigned short *source_index;
    Entry *entries;
    char pad_0c[0x20];
    unsigned short current_index;
} WorkState;

extern WorkState *data_02174e48;
extern int func_0202edfc(void);

void func_0202edd0(void)
{
    WorkState *state;
    unsigned int index;
    short value;

    state = data_02174e48;
    index = func_0202edfc();
    index = index + *state->source_index;
    value = state->entries[index].value;
    state->entries[state->current_index].value = value;
}
