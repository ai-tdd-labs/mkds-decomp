// PURPOSE: Runs the Wireless LAN menu scene loop with its default settings.
// The scene object is passed through to the common scene-loop handler.
// It probably supplies a fixed 36-byte configuration block for this menu.

typedef unsigned int u32;

typedef struct {
    u32 words[8];
} WLMenuSceneParams;

extern const WLMenuSceneParams data_021651b0;
extern void OnSceneLoop(void *scene, WLMenuSceneParams *params);

int SceneFn_WLMenu(void *scene)
{
    WLMenuSceneParams params = data_021651b0;

    OnSceneLoop(scene, &params);
    return 0;
}
