// PURPOSE: Updates the logo scene state each frame.
// The argument is probably the current scene state and may be absent.
// It advances the logo state handler, then clears the scene flag while the
// shared logo context is in state 11 before updating navigation contexts.

typedef unsigned short u16;

typedef struct LogoContext {
    char pad_00[0x18];
    int stateHandler;
    char pad_1c[0x26 - 0x1c];
    u16 state;
} LogoContext;

typedef struct SceneLogo {
    char pad_00[4];
    u16 flag;
} SceneLogo;

extern LogoContext *data_021a99e0;
extern void StateDualHandler_Execute(void *handler);
extern void NavigationContext_OnSceneUpdate_from_thumb(void);

void Scene_Logo_UpdateImpl(SceneLogo *scene)
{
    StateDualHandler_Execute(&data_021a99e0->stateHandler);

    if (scene != 0) {
        if (data_021a99e0->state == 11) {
            scene->flag = 0;
        }
    }

    NavigationContext_OnSceneUpdate_from_thumb();
}
