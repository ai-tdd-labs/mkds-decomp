/* PURPOSE: Marks the race scene as suspended.
 * This routine does nothing unless the scene state is active.
 * It probably suspends the owned subsystem once, then records that state.
 * The function takes no arguments and returns no value.
 */

typedef struct Struct59C4Sub Struct59C4Sub;

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
    Struct59C4Sub *subsystem;
} SceneState;

extern SceneState *data_021759c4;
extern void Struct59C4Sub_SomeFn_2(Struct59C4Sub *subsystem);

void func_02046e84(void)
{
    SceneState *scene = data_021759c4;

    if (!scene->flags.bits.active) {
        return;
    }

    if (!scene->flags.bits.suspended) {
        Struct59C4Sub_SomeFn_2(scene->subsystem);
    }

    /* Reload the global scene pointer after the call, as in the original. */
    data_021759c4->flags.value |= 4;
}
