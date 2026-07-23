// PURPOSE: Records controller input in a compact playback buffer.
// The first argument owns the recording buffer and current run index.
// The second argument contains the current controller buttons.
// Repeated samples extend a run; a full buffer is finalized for later use.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputRecordEntry {
    u8 keys;
    u8 duration;
} InputRecordEntry;

typedef struct InputRecord {
    u32 dataLength;
    InputRecordEntry entries[0x6e4];
} InputRecord;

typedef struct InputRecorder {
    InputRecord *record;
    u16 currentEntry;
    u16 waitCounter;
    u32 state;
    u32 bufferCleared;
} InputRecorder;

extern void DC_SomeClean(void *buffer, int size);

void func_0204a798(InputRecorder *recorder, u16 buttons)
{
    int startNew = 0;
    u8 encoded = 0;
    InputRecordEntry *entry;

    if (recorder->state != 1) {
        return;
    }

    entry = &recorder->record->entries[recorder->currentEntry];

    encoded |= (buttons & 0x001) ? 0x01 : 0;
    encoded |= (buttons & 0x002) ? 0x02 : 0;
    encoded |= (buttons & 0x100) ? 0x04 : 0;
    encoded |= (buttons & 0x600) ? 0x08 : 0;
    encoded |= (buttons & 0x010) ? 0x10 : 0;
    encoded |= (buttons & 0x020) ? 0x20 : 0;
    encoded |= (buttons & 0x080) ? 0x40 : 0;
    encoded |= (buttons & 0x040) ? 0x80 : 0;

    if (entry->duration != 0 && entry->keys != encoded) {
        startNew = 1;
    } else if (entry->duration >= 0xff) {
        startNew = 1;
    }

    if (startNew != 0) {
        if (recorder->currentEntry >= 0x6e4) {
            if (recorder->state != 1) {
                return;
            }

            recorder->record->dataLength = recorder->currentEntry << 1;
            recorder->state = 3;
            DC_SomeClean(recorder->record, 0xdcc);
            return;
        }

        entry++;
        recorder->currentEntry++;
        entry->duration = 0;
    }

    entry->keys = encoded;
    entry->duration++;
}
