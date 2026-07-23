// PURPOSE: Clears the saved data for one entry.
// The entry number is one-based.
// It probably resets a 30-byte record and its associated state value.

typedef struct EntryStorage {
    char records[0x1e0];
    int states[1];
} EntryStorage;

extern void Mem_CpuFill8(void *destination, int value, unsigned int size);
extern EntryStorage *data_0216fdf4;

void func_0200c3fc(int entry)
{
    int index;

    if (data_0216fdf4 != 0) {
        index = entry - 1;
        Mem_CpuFill8(data_0216fdf4->records + (index << 5), 0, 0x1e);
        data_0216fdf4->states[index] = 0;
    }
}
