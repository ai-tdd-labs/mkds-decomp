// PURPOSE: Clears the current scene subsystem.
// The global scene state probably owns a subsystem pointer.
// This function notifies that subsystem before removing the global state.

typedef struct {
    char padding[0x3c];
    void *subsystem;
} SceneState;

extern SceneState *data_021759c4;
extern void Maybe_helper_10f114(void *a0);

void ResetGlobal59C4(void) {
    Maybe_helper_10f114(data_021759c4->subsystem);
    data_021759c4 = 0;
}
