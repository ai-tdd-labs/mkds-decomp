// PURPOSE: Clears every saved game data section.
// The preserveUserName argument is forwarded only to the header reset.
// It clears the independent save sections before resetting the header.

extern void ClearSaveDataSection_Emblem_from_thumb(void);
extern void ClearSaveDataSection_GrandPrix_from_thumb(void);
extern void ClearSaveDataSection_TimeTrials_from_thumb(void);
extern void ClearSaveDataSection_MissionRun_from_thumb(void);
extern void ClearSaveDataGhosts_from_thumb(void);
extern void ClearSaveDataSection_FriendList_from_thumb(void);
extern void ClearSaveDataSection_Header_from_thumb(int preserveUserName);

void ClearAllSaveDataSections_from_thumb(int preserveUserName)
{
    ClearSaveDataSection_Emblem_from_thumb();
    ClearSaveDataSection_GrandPrix_from_thumb();
    ClearSaveDataSection_TimeTrials_from_thumb();
    ClearSaveDataSection_MissionRun_from_thumb();
    ClearSaveDataGhosts_from_thumb();
    ClearSaveDataSection_FriendList_from_thumb();
    ClearSaveDataSection_Header_from_thumb(preserveUserName);
}
