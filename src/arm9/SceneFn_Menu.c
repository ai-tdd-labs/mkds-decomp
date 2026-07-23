// PURPOSE: Starts the menu scene loop with its callbacks.
// Receives the scene state as its first argument.
// Copies the probably read-only menu scene descriptor before starting it.

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

extern char data_021646f8[];
extern void OnSceneLoop(void *scene, SceneCallbacks *callbacks);

int SceneFn_Menu(void *scene)
{
    SceneCallbacks callbacks = *(SceneCallbacks *)data_021646f8;

    OnSceneLoop(scene, &callbacks);
    return 0;
}
