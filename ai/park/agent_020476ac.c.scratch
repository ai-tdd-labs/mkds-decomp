/*
PURPOSE: Reloads the archives needed for the current scene.
This function takes no arguments and probably prepares the common scene archives.
It disposes archive 10, mounts archives 1, 5, 14, and 16, then restores heap group 9.
*/

extern int GetCurrentSceneId(void);
extern void Arc_DisposeArchive_from_thumb(int index);
extern void SetActiveExecutionContextHeapGroupId_from_thumb(int id);
extern void Arc_MountArchive_from_thumb(int index, int scene);

void func_020476ac(void)
{
    int sceneId = GetCurrentSceneId();

    Arc_DisposeArchive_from_thumb(10);
    SetActiveExecutionContextHeapGroupId_from_thumb(0);
    Arc_MountArchive_from_thumb(1, sceneId);
    Arc_MountArchive_from_thumb(5, sceneId);
    Arc_MountArchive_from_thumb(14, sceneId);
    Arc_MountArchive_from_thumb(16, sceneId);
    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
