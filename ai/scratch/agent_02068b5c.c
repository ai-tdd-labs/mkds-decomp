// PURPOSE: Marks a racer entry as processed before updating it.
// The argument is probably an MQRacerEntry object.
// Entries already carrying the processing flag are left untouched.
// Otherwise the flag is set and the matching follow-up routine is called.
typedef struct {
    char _pad[0x7c];
    volatile int flags;
} StructMQRacerEntry;

extern void StructMQRacerEntry_SomeFn_35(void *a0, int a1);

void StructMQRacerEntry_SomeFn_52(StructMQRacerEntry *entry)
{
    if (entry->flags & 0x40000) {
        return;
    }

    entry->flags |= 0x40000;
    StructMQRacerEntry_SomeFn_35(entry, 0);
}
