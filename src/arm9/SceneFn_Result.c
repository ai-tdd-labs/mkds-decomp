// PURPOSE: Runs the result scene with its fixed settings.
// The scene is passed unchanged to the common scene-loop handler.
// The copied settings probably configure the result screen.

typedef unsigned int u32;

typedef struct {
    u32 words[8];
} ResultSceneParams;

extern const ResultSceneParams data_02165368;
extern void OnSceneLoop(void *scene, ResultSceneParams *params);

int SceneFn_Result(void *scene)
{
    ResultSceneParams params = data_02165368;

    OnSceneLoop(scene, &params);
    return 0;
}
