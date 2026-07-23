// PURPOSE: Creates and clears a list of sound entries.
// The output receives its entry count and an allocated entry array.
// Each entry is initialized with an invalid identifier and empty fields.

typedef struct SoundContext SoundContext;
typedef void (*SoundDisposeCallback)(void);

typedef struct SoundEntry {
    int id;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
} SoundEntry;

typedef struct SoundEntryList {
    int count;
    SoundEntry *entries;
} SoundEntryList;

extern void *Sound_Context_Allocate(SoundContext *context, unsigned int payloadSize,
                                    SoundDisposeCallback disposeCallback, void *soundArchive,
                                    void *customArgument);

void func_0210e094(SoundEntryList *list, int count, SoundContext *context)
{
    int index;

    list->count = count;
    list->entries = Sound_Context_Allocate(context, count << 4, 0, 0, 0);
    index = 0;
    if (list->count > 0) {
        do {
            list->entries[index].id = -1;
            list->entries[index].unknown_04 = 0;
            list->entries[index].unknown_08 = 0;
            list->entries[index].unknown_0c = 0;
            index++;
        } while (index < list->count);
    }
}
