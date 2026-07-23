// PURPOSE: Sends a saved scene record to the active scene loop.
// The input is forwarded as the first argument to the scene-loop handler.
// A probably fixed 32-byte record is copied to temporary stack storage first.

typedef struct SceneRecord {
    unsigned int words[8];
} SceneRecord;

extern const SceneRecord data_0216524c;
extern void OnSceneLoop(void *scene, SceneRecord *record);

int SceneFn_Record(void *scene)
{
    SceneRecord record = data_0216524c;

    OnSceneLoop(scene, &record);
    return 0;
}
