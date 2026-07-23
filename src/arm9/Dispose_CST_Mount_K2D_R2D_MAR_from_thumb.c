extern int GetCurrentSceneId(void);
extern void Arc_DisposeArchive_from_thumb(int index);
extern void SetActiveExecutionContextHeapGroupId_from_thumb(int id);
extern void Arc_MountArchive_from_thumb(int idx, int scene);

void Dispose_CST_Mount_K2D_R2D_MAR_from_thumb(void)
{
    // PURPOSE: Disposes the CST archive and mounts scene-two interface archives.
    Arc_DisposeArchive_from_thumb(13);
    SetActiveExecutionContextHeapGroupId_from_thumb(0);
    if (GetCurrentSceneId() == 2) {
        Arc_MountArchive_from_thumb(5, 2);
        Arc_MountArchive_from_thumb(11, 2);
        Arc_MountArchive_from_thumb(0, 2);
    }
    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
