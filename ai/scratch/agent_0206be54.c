// PURPOSE: Starts collision handling when a driver state allows it.
// The first argument is the driver entry and the second selects a state path.
// Disabled flags and unsupported active states reject the collision.

typedef struct StructMQRacerEntry {
    char pad_00[0x48];
    unsigned int field_48;
    unsigned int field_4c;
    char pad_50[0x7c - 0x50];
    unsigned int field_7c;
    char pad_80[0x180 - 0x80];
    int field_180;
} StructMQRacerEntry;

extern void DriverContext_HandleSomeCollision(StructMQRacerEntry *entry,
                                               int mode);

int func_0206be54(StructMQRacerEntry *entry, int mode)
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
    if (mode == 1) {
        goto selected_mode;
    }
    if (mode != 2) {
        goto other_mode;
    }

selected_mode:
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
    goto result_ready;

other_mode:
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
    if (result == 0) {
        return 0;
    }

    DriverContext_HandleSomeCollision(entry, mode);
    return 1;
}
