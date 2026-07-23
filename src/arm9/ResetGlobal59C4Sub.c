/* PURPOSE: Releases the active scene subsystem and clears its state.
 * This routine takes no arguments and returns no value.
 * It does nothing when the scene is not active.
 * The helper probably releases the subsystem owned by the scene.
 */

typedef union SceneStateFlags {
    unsigned int value;
    struct {
        signed int unknown0 : 1;
        signed int active : 1;
        signed int suspended : 1;
        signed int remaining : 29;
    } bits;
} SceneStateFlags;

typedef struct SceneState {
    unsigned char padding_00[0x30];
    SceneStateFlags flags;
    unsigned char padding_34[8];
    void *subsystem;
} SceneState;

extern SceneState *data_021759c4;
extern void Maybe_helper_10f0d8(void *subsystem);

void ResetGlobal59C4Sub(void)
{
    SceneState *scene = data_021759c4;

    if (!scene->flags.bits.active) {
        return;
    }

    Maybe_helper_10f0d8(scene->subsystem);
    data_021759c4->subsystem = 0;
    data_021759c4->flags.value &= ~2;
    data_021759c4->flags.value &= ~4;
}
