// PURPOSE: Replaces the KM1 archive with the KM2 archive for scene 2.
// This function takes no arguments.
// It disposes archive 6, selects heap group 0, and mounts archive 7.
// It probably prepares the KM2 assets for the active scene.

extern void Arc_DisposeArchive_from_thumb(int index);
extern void SetActiveExecutionContextHeapGroupId_from_thumb(int id);
extern void Arc_MountArchive_from_thumb(int idx, int scene);

void Dispose_KM1_Mount_KM2_from_thumb(void)
{
    Arc_DisposeArchive_from_thumb(6);
    SetActiveExecutionContextHeapGroupId_from_thumb(0);
    Arc_MountArchive_from_thumb(7, 2);
    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
