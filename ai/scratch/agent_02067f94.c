// PURPOSE: Marks an eligible racer entry as complete.
// The entry and its caller-provided context are passed to a helper
// when the entry state allows completion. An enabled entry also increments a
// global counter before its completion flag is set.

typedef struct StructMQRacerEntry {
    char pad_00[0x48];
    unsigned int field_48;
    unsigned int field_4c;
    char pad_50[0x7c - 0x50];
    unsigned int field_7c;
    char pad_80[0x180 - 0x80];
    int field_180;
} StructMQRacerEntry;

typedef struct GlobalRK {
    char pad_00[0x14];
    int field_14;
} GlobalRK;

extern void StructMQRacerEntry_SomeFn_4(StructMQRacerEntry *entry, int context, int value);
extern GlobalRK *GetGlobalRK(void);

#pragma optimize_for_size on

int func_02067f94(StructMQRacerEntry *entry, int context)
{
    if ((entry->field_4c & 0x400000) != 0) {
        return 0;
    } else if ((entry->field_7c & 0x200) != 0) {
        if ((entry->field_180 != 0) || ((entry->field_48 & 0x1800) != 0)) {
            return 0;
        } else if ((entry->field_4c & 0x10000040) == 0) {
            StructMQRacerEntry_SomeFn_4(entry, context, 0);
        } else {
            return 0;
        }
    } else {
        int allowed = 1;

        if (((entry->field_4c & 0x10000040) != 0) ||
            ((entry->field_48 & 0x1800) != 0)) {
        } else {
            int invalid = 0;

            if (entry->field_180 != 0) {
                if (entry->field_180 != 1) {
                    if (entry->field_180 != 2) {
                        invalid = allowed;
                    }
                }
            }
            if (invalid == 0) {
                allowed = 0;
            }
        }
        if (allowed == 0) {
            StructMQRacerEntry_SomeFn_4(entry, context, 0);
        } else {
            return 0;
        }
    }

    if ((entry->field_7c & 1) != 0) {
        GetGlobalRK()->field_14++;
    }
    entry->field_48 |= 0x20000;
    return 1;
}
