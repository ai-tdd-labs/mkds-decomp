// PURPOSE: Decides whether a racer entry can advance.
// The entry and its probably related context are passed to a follow-up action.
// It rejects disabled states, then marks accepted entries as active.
// An accepted flagged entry probably also increments the global racer counter.

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

extern void StructMQRacerEntry_SomeFn_59(StructMQRacerEntry *entry,
                                          void *context, int mode);
extern GlobalRK *GetGlobalRK(void);

int StructMQRacerEntry_SomeFn_72(StructMQRacerEntry *entry, void *context)
{
    int result;

    if ((entry->field_4c & 0x400000) != 0) {
        result = 0;
        goto result_ready;
    }
    if ((entry->field_7c & 0x200) == 0) {
        goto inactive;
    }
    if (entry->field_180 != 0) {
        goto active_fail;
    }
    if ((entry->field_48 & 0x1800) != 0) {
        goto active_fail;
    }
    if ((entry->field_4c & 0x10000040) == 0) {
        result = 1;
        goto result_ready;
    }
active_fail:
    result = 0;
    goto result_ready;

inactive:
    {
        int allowed = 1;

        if ((entry->field_4c & 0x10000040) == 0) {
            if ((entry->field_48 & 0x1800) == 0) {
                int state = entry->field_180;
                int other = 0;

                if (state != 0) {
                    if (state != 1) {
                        if (state != 2) {
                            other = allowed;
                        }
                    }
                }
                if (other == 0) {
                    allowed = 0;
                }
            }
        }
        if (allowed == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

result_ready:
    if (result != 0) {
        StructMQRacerEntry_SomeFn_59(entry, context, 0);
        result = 1;
    }
    if (result == 0) {
        return 0;
    }
    if ((entry->field_7c & 1) != 0) {
        GetGlobalRK()->field_14++;
    }
    {
        int flags = entry->field_48;
        flags |= 0x20000;
        entry->field_48 = flags;
        return flags;
    }
}
