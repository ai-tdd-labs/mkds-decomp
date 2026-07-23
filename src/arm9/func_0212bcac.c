// PURPOSE: Moves a sound player to its requested priority list.
// The entry records its current list at offset 4 and its requested priority at offset 0x3d.
// It is removed from its old list and the global list before being placed in the new one.
// The exact meaning of the priority byte is probably an internal sound ordering setting.

typedef unsigned char u8;

typedef struct SoundPlayerEntry {
    u8 unknown00[4];
    void *list;
    u8 unknown08[0x35];
    u8 priority;
} SoundPlayerEntry;

extern unsigned char data_0217d450[];
extern void IntrusiveListWrapper_RemoveItem(void *list, void *item);
extern void func_0212bf14(void *list, SoundPlayerEntry *newEntry);
extern void func_0212beb4(SoundPlayerEntry *newEntry);

void func_0212bcac(SoundPlayerEntry *newEntry, u8 priority)
{
    void *oldList = newEntry->list;

    if (oldList != 0) {
        IntrusiveListWrapper_RemoveItem(oldList, newEntry);
        newEntry->list = 0;
    }

    IntrusiveListWrapper_RemoveItem(data_0217d450, newEntry);
    newEntry->priority = priority;

    if (oldList != 0) {
        func_0212bf14(oldList, newEntry);
    }

    func_0212beb4(newEntry);
}
