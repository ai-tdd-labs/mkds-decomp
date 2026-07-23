/* PURPOSE: Adds a sound player to the global priority list.
 * The argument is the player entry to insert.
 * Entries are ordered by the priority byte at offset 0x3d, probably from
 * lowest to highest; equal-priority entries remain ahead of the new entry. */

typedef struct SoundPlayerEntry {
    unsigned char reserved[0x3d];
    unsigned char priority;
} SoundPlayerEntry;

extern SoundPlayerEntry *IntrusiveListWrapper_NextItem(void *list, void *item);
extern void IntrusiveListWrapper_SomeFn_0(void *list, void *where, void *item);
extern unsigned char data_0217d450[];

void func_0212beb4(SoundPlayerEntry *newEntry)
{
    SoundPlayerEntry *current = IntrusiveListWrapper_NextItem(data_0217d450, 0);

    while (current != 0) {
        if (newEntry->priority < current->priority) {
            break;
        }
        current = IntrusiveListWrapper_NextItem(data_0217d450, current);
    }

    IntrusiveListWrapper_SomeFn_0(data_0217d450, current, newEntry);
}
