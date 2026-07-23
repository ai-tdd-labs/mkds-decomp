// PURPOSE: Marks a racer entry as initialized after preparing it.
// The entry is skipped when its state field already has the sentinel value.
// It probably prepares the entry with its current state before setting that sentinel.

typedef struct {
    unsigned char pad000[0x488];
    int state;
} StructMQRacerEntry;

extern void StructMQRacerEntry_SomeFn_75(StructMQRacerEntry *entry, int zero0,
                                         int state, int zero1);

void StructMQRacerEntry_SomeFn_70(StructMQRacerEntry *entry)
{
    if (entry->state == 0xffff) {
        return;
    }

    StructMQRacerEntry_SomeFn_75(entry, 0, entry->state, 0);
    entry->state = 0xffff;
}
