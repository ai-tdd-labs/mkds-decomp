// PURPOSE: Checks whether a kart selection entry is unlocked.
// The entry is selected from a 13-byte table using an offset and index.
// It probably uses save data to avoid querying the extra-kart unlock flags.

typedef unsigned char u8;

typedef struct UnkStruct_0217aa00 {
    int state;
    int unk4;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern u8 *data_0217aa08;
extern int CheckExtraKartUnlockFlags_from_thumb(void);

int func_0205fc98(void **table, int offset, int index)
{
    int useSaveUnlock = 0;
    int state;
    unsigned int unlockFlags;

    if (data_0217aa00 == 0) {
        state = 0;
    } else {
        state = data_0217aa00->state;
    }
    if (state != 0 && data_0217aa00->unk4 != 13) {
        useSaveUnlock = 1;
    }

    if (useSaveUnlock != 0) {
        unlockFlags = data_0217aa08[0x39];
    } else {
        unlockFlags = CheckExtraKartUnlockFlags_from_thumb();
    }

    {
        unsigned char *entries;
        unsigned int required;

        entries = (unsigned char *)*table;
        entries += index * 13;
        entries += offset;
        required = entries[6];
        if (required != 0 && required <= unlockFlags) {
            return 1;
        }
    }

    return 0;
}
