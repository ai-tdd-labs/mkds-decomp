// PURPOSE: Starts the keyboard scene loop with its callbacks.
// Receives the scene state as its first argument.
// Copies the probably read-only keyboard scene descriptor before starting it.

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

extern char data_0216e8e0[];
extern void OnSceneLoop(void *scene, SceneCallbacks *callbacks);

int SceneFn_Keyboard_from_thumb(void *scene)
{
    SceneCallbacks callbacks = *(SceneCallbacks *)data_0216e8e0;

    OnSceneLoop(scene, &callbacks);
    return 0;
}
