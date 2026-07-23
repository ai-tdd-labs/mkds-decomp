// PURPOSE: Inserts a sound player into a priority list.
// The list and player entry are supplied by the caller.
// Entries are ordered by their priority byte; equal priorities stay ahead.

typedef struct SoundPlayerEntry {
    unsigned char reserved_00[4];
    void *list;
    unsigned char reserved_08[0x35];
    unsigned char priority;
} SoundPlayerEntry;

extern SoundPlayerEntry *IntrusiveListWrapper_NextItem(void *list, void *item);
extern void IntrusiveListWrapper_SomeFn_0(void *list, void *where, void *item);

void func_0212bf14(void *list, SoundPlayerEntry *newEntry)
{
    SoundPlayerEntry *current = IntrusiveListWrapper_NextItem(list, 0);

    while (current != 0) {
        if (newEntry->priority < current->priority) {
            break;
        }
        current = IntrusiveListWrapper_NextItem(list, current);
    }

    IntrusiveListWrapper_SomeFn_0(list, current, newEntry);
    newEntry->list = list;
}
