// PURPOSE: Mounts the archive selected by the current mount entry.
// It uses the active archive data and its matching scene archive name.
// On success, it records that the runtime entry has been mounted.

#pragma optimize_for_size on

typedef struct ArcRuntimeEntry {
    unsigned char padding_00[0x68];
    int mounted;
    void *archive;
} ArcRuntimeEntry;

typedef struct ArcHeapRef {
    void *archive;
    int padding_04;
    int entryIndex;
} ArcHeapRef;

typedef struct ArcRuntimeState {
    ArcRuntimeEntry entries[19];
    unsigned char padding_850[0x78];
    ArcHeapRef heapRefs[16];
} ArcRuntimeState;

extern ArcRuntimeState *data_021759c8;
extern char *data_02164e04[];

extern int MountMountEntryFrom(void *entry, char *name, void *archiveData);

void MountCurrentMountEntry_from_thumb(void)
{
    ArcHeapRef *heapRef;
    ArcRuntimeEntry *entry;
    ArcRuntimeState *state;

    state = data_021759c8;
    heapRef = state->heapRefs;
    entry = &state->entries[heapRef[11].entryIndex];
    if (heapRef[11].archive != 0) {
        if (MountMountEntryFrom(entry, data_02164e04[heapRef[11].entryIndex],
                                heapRef[11].archive) != 0) {
            entry->mounted = 1;
            entry->archive = heapRef[11].archive;
        }
    }
}
