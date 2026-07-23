// PURPOSE: Runs the logo scene loop with its fixed settings.
// The scene object is forwarded unchanged to the shared scene-loop handler.
// It probably supplies a fixed 32-byte configuration for the logo scene.

typedef unsigned int u32;

typedef struct {
    u32 words[8];
} LogoSceneParams;

extern const LogoSceneParams data_02165280;
extern void OnSceneLoop(void *scene, LogoSceneParams *params);

int SceneFn_Logo(void *scene)
{
    LogoSceneParams params = data_02165280;

    OnSceneLoop(scene, &params);
    return 0;
}
