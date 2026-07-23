// PURPOSE: Runs the emblem scene update using its fixed parameter block.
// The input is probably the active scene object.
// A 32-byte constant block is copied onto the stack for the scene loop.

typedef struct {
    unsigned int words[8];
} EmblemSceneParams;

extern const EmblemSceneParams data_02165190;
extern void OnSceneLoop(void *scene, EmblemSceneParams *params);

int SceneFn_Emblem(void *scene)
{
    EmblemSceneParams params = data_02165190;

    OnSceneLoop(scene, &params);
    return 0;
}
