// PURPOSE: Marks a racer state and reports completion.
// The first argument is probably a racer entry and the second receives status 7.
// When the entry check succeeds, this sets its completion flag.
// An enabled entry flag also increments a probably global counter.

typedef struct StructMQRacerEntry {
    char pad_00[0x48];
    unsigned int field_48;
    char pad_4c[0x7c - 0x4c];
    unsigned int field_7c;
} StructMQRacerEntry;

typedef struct GlobalRK {
    char pad_00[0x14];
    int field_14;
} GlobalRK;

extern int StructMQRacerEntry_SomeFn_65(StructMQRacerEntry *entry, int *status);
extern GlobalRK *GetGlobalRK(void);

int func_02067cb0(StructMQRacerEntry *entry, int *status)
{
    if (StructMQRacerEntry_SomeFn_65(entry, status) != 0) {
        if ((entry->field_7c & 1) != 0) {
            GetGlobalRK()->field_14++;
        }
        entry->field_48 |= 0x20000;
    }
    *status = 7;
    return 2;
}
