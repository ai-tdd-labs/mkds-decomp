// PURPOSE: Starts the ghost scene loop with its scene callbacks.
// Receives the scene state as its first argument.
// Copies the probably read-only ghost scene descriptor from ROM before use.

typedef struct SceneCallbacks {
    int update;
    int vblank;
    int finalize;
    int unknown_0C;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1C;
} SceneCallbacks;

extern char data_021653c0[];
extern void OnSceneLoop(void *scene, SceneCallbacks *callbacks);

int SceneFn_Ghost(void *scene)
{
    SceneCallbacks callbacks = *(SceneCallbacks *)data_021653c0;

    OnSceneLoop(scene, &callbacks);
    return 0;
}
