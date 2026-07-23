// PURPOSE: Advances a driver's route tracker and updates its movement direction.
// The tracker chooses a linked route node from the current path state.
// It updates the driver's animation and direction flag, then normalizes the
// movement vector between the previous and current nodes.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad00[4];
    s16 animationIndex;
    s16 directionFlag;
} PathValue;

typedef struct StateNode {
    char pad00[0x18];
    VecFx32 *position;
    char pad1c[4];
    PathValue *pathValue;
    u16 pathCount;
} StateNode;

typedef struct {
    char pad00[0x1a];
    u16 animation;
} DriverAnimation;

typedef struct {
    char pad00[8];
    DriverAnimation *animation;
} DriverAnimationHolder;

typedef struct {
    char pad00[0x7c];
    u32 flags;
    char pad80[0x510];
    DriverAnimationHolder *animationHolder;
} DriverEntry;

typedef struct {
    StateNode *current;
    StateNode *previous;
    VecFx32 direction;
    char pad14[8];
    u16 driverId;
    u8 pathPhase;
} DriverTracker;

extern u32 data_021557dc[];
extern DriverEntry *GetDriverEntry(u16 id);
extern void DriverContext_UpdateCharacterAnimation(DriverEntry *driver,
                                                    u32 animation,
                                                    int enable);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);

void func_0207fd28(DriverTracker *tracker)
{
    DriverEntry *driver;
    u16 index;

    driver = GetDriverEntry(tracker->driverId);

    if ((u32)tracker->current->pathCount > 1
        && (u32)tracker->pathPhase < 2) {
        if (tracker->pathPhase == 0) {
            index = tracker->driverId / 3;
        } else {
            index = tracker->driverId % 3;
        }
        tracker->pathPhase++;
    } else {
        index = 0;
    }

    tracker->previous = tracker->current;
    tracker->current = ((StateNode **)tracker->current)[index];

    if (driver->animationHolder->animation->animation
        != data_021557dc[tracker->current->pathValue->animationIndex]) {
        DriverContext_UpdateCharacterAnimation(
            driver,
            data_021557dc[tracker->current->pathValue->animationIndex], 1);
    }

    if (tracker->driverId != 0) {
        if (tracker->current->pathValue->directionFlag == 0) {
            driver->flags &= ~0x40;
        } else {
            driver->flags |= 0x40;
        }
    }

    VecFx32_Subtract(tracker->current->position, tracker->previous->position,
                     &tracker->direction);
    Vector3_MaybeNormalize(&tracker->direction, &tracker->direction);
}
