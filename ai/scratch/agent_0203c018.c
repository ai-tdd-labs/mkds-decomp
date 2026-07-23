// PURPOSE: Runs the title screen scene loop with its title configuration.
/*
 * The scene argument is passed unchanged to the main scene loop.
 * The fixed 32-byte configuration is copied to stack storage before the call.
 * Its exact fields are probably title-screen setup parameters.
 */

typedef struct SceneTitleConfig {
    unsigned int words[8];
} SceneTitleConfig;

extern const SceneTitleConfig data_02164798;
extern void OnSceneLoop(void *scene, SceneTitleConfig *config);

int SceneFn_Title(void *scene)
{
    SceneTitleConfig config = data_02164798;

    OnSceneLoop(scene, &config);
    return 0;
}
