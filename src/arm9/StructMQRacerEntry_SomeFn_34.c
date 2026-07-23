// PURPOSE: Marks a racer entry as active after setup.
// The entry is first configured with mode 1.
// It then enables a state flag at offset 0x7c.
// The flag probably tracks racer-entry state.

typedef unsigned int u32;

extern void StructMQRacerEntry_SomeFn_35(void *entry, int mode);

void StructMQRacerEntry_SomeFn_34(void *entry) {
    char *racer = (char *)entry;

    StructMQRacerEntry_SomeFn_35(racer, 1);
    *(u32 *)(racer + 0x7c) |= 0x800000; // Enable the entry state flag.
}
