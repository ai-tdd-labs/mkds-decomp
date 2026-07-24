// PURPOSE: Activates a racer action and flips its linked state flag.
// The argument is probably a racer entry.
// It returns zero when the action cannot start.
// On success, it performs the action and conditionally toggles a linked flag.

typedef unsigned int u32;

typedef struct LinkedRacerState {
    char pad_00[0x2c];
    u32 flags_2c;
} LinkedRacerState;

typedef struct StructMQRacerEntry {
    char pad_00[0x7c];
    u32 flags_7c;
    char pad_80[0x514 - 0x80];
    LinkedRacerState *linked_state_514;
} StructMQRacerEntry;

extern int func_0206be54(StructMQRacerEntry *entry, int mode);
extern void StructMQRacerEntry_SomeFn(StructMQRacerEntry *entry);

int func_0206bab8(StructMQRacerEntry *entry)
{
    if (func_0206be54(entry, 6) == 0) {
        return 0;
    }

    StructMQRacerEntry_SomeFn(entry);
    if ((entry->flags_7c & 0x200) != 0) {
        entry->linked_state_514->flags_2c ^= 0x20000;
    }

    return 1;
}
