// PURPOSE: Replaces the KM2 and KSB archives with CRS for scene 2.
// This function takes no arguments.
// It disposes two archives, switches the heap group, and conditionally mounts CRS.
// It probably prepares scene-specific course resources.

extern void Arc_DisposeArchive_from_thumb(int index);
extern void SetActiveExecutionContextHeapGroupId_from_thumb(int id);
extern int GetCurrentSceneId(void);
extern void Arc_MountArchive_from_thumb(int idx, int scene);

void Dispose_KM2_KSB_Mount_CRS_from_thumb(void)
{
    Arc_DisposeArchive_from_thumb(7);
    Arc_DisposeArchive_from_thumb(8);
    SetActiveExecutionContextHeapGroupId_from_thumb(0);

    if (GetCurrentSceneId() == 2) {
        Arc_MountArchive_from_thumb(3, 2);
    }

    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
