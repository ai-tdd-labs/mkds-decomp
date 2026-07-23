// PURPOSE: Updates this queue entry's delay and completion flag.
// The entry probably stores a driver index and two signed frame counters.
// It reports whether the active counter wrapped this frame.

typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct DriverEntry {
    char pad_00[0x44];
    u32 flags;
} DriverEntry;

typedef struct StructMQSub2 {
    char pad_00[0x24];
    u16 driver_index;
    s16 active_counter;
    s16 delay_counter;
} StructMQSub2;

extern DriverEntry *GetDriverEntry(u16 driver_index);

int StructMQSub2_SomeFn_0(StructMQSub2 *entry)
{
    int wrapped = 0;
    int active = 0;

    entry->delay_counter--;
    if (entry->delay_counter <= 0) {
        entry->delay_counter = 0;
    } else {
        active = 1;
    }

    if (GetDriverEntry(entry->driver_index)->flags & 0xC0) {
        entry->delay_counter = 5;
        active = 1;
    }

    if (active) {
        entry->active_counter++;
        if (entry->active_counter >= 0x78) {
            entry->active_counter = 0;
            wrapped = 1;
        }
    } else if (entry->delay_counter <= 0) {
        entry->active_counter = 0;
    }

    return wrapped;
}
