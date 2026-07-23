// PURPOSE: Updates a racer entry when its active state allows it.
// It prepares the entry unless a pair of state flags blocks that step.
// The final update probably clears a temporary racer condition.

typedef struct {
    unsigned char pad000[0x48];
    int flags48;
    unsigned char pad04c[0x30];
    int flags7c;
    unsigned char pad080[0x34c];
    void *entry3cc;
} StructMQRacerEntry;

extern void StructMQRacerEntry_SomeFn_5(StructMQRacerEntry *entry, void *entry3cc,
                                        int value);
extern void StructMQRacerEntry_SomeFn_7(StructMQRacerEntry *entry, int value,
                                        int zero);

void StructMQRacerEntry_SomeFn_89(StructMQRacerEntry *entry)
{
    if (!(entry->flags48 & 0x840)) {
        StructMQRacerEntry_SomeFn_5(entry, entry->entry3cc, 8);
    }

    if (!(entry->flags7c & 0x10)) {
        return;
    }

    if (entry->flags7c & 0x30000) {
        return;
    }

    StructMQRacerEntry_SomeFn_7(entry, 2, 0);
}
