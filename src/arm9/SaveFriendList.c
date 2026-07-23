// PURPOSE: Saves the friend list to save data.
// The save-data holder probably owns the friend-list section at offset 0x20.
// It writes that section first, then updates the save-data header.

typedef struct SaveDataHolder {
    char pad_00[0x20];
    void *friend_list;
} SaveDataHolder;

extern SaveDataHolder *data_0217aa08;
extern void WriteSaveDataSection_FriendList_from_thumb(void *friend_list);
extern void WriteSaveDataHeader_from_thumb(void);

void SaveFriendList(void)
{
    // Save the friend-list payload before committing its header.
    WriteSaveDataSection_FriendList_from_thumb(data_0217aa08->friend_list);
    WriteSaveDataHeader_from_thumb();
}
