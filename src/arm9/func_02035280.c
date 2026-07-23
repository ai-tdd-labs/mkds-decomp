// PURPOSE: Starts the next available dialog sound.
// The argument permits wrapping from the last slot back to the first slot.
// It probably selects a ready dialog entry and starts sequence zero for it.

typedef struct DialogSoundEntry {
    unsigned int state;
    unsigned int ready;
    unsigned char padding[0x34];
} DialogSoundEntry;

typedef struct DialogSoundWork {
    unsigned char padding0[0x80];
    int currentEntry;
    unsigned char padding1[0x40];
    DialogSoundEntry entries[4];
} DialogSoundWork;

extern DialogSoundWork *data_02174e64;
extern unsigned char data_0217d068[];
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);

void func_02035280(int allowWrap)
{
    int entry;
    int found;

    found = 0;
    entry = data_02174e64->currentEntry + 1;
    if (entry >= 4) {
        if (allowWrap == 0) {
            return;
        }
        entry = found;
    }

    while (entry != data_02174e64->currentEntry) {
        if ((data_02174e64->entries[entry].state == 1) &&
            (data_02174e64->entries[entry].ready == 1)) {
            found = 1;
            data_02174e64->currentEntry = entry;
            break;
        }

        entry++;
        if (entry >= 4) {
            if (allowWrap == 0) {
                return;
            }
            entry = 0;
        }
    }

    if (found != 0) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 0);
    }
}
