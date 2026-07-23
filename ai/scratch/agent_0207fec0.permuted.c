// PURPOSE: Advances a driver tracker to its next linked state and updates its direction.

typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad00[4];
    s16 f4;
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
    char pad00[0x590];
    DriverAnimationHolder *animationHolder;
} DriverEntry;

typedef struct {
    StateNode *current;
    StateNode *previous;
    VecFx32 direction;
    char pad14[8];
    u16 driverId;
} DriverTracker;

extern unsigned int data_021557dc[];
extern DriverEntry *GetDriverEntry(u16 id);
extern void DriverContext_UpdateCharacterAnimation(DriverEntry *driver,
                                                    unsigned int animation,
                                                    int enable);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);

void func_0207fec0(DriverTracker *tracker)
{
    DriverEntry *driver;
    int index;

    index = 0;
    driver = GetDriverEntry(tracker->driverId);
    if (tracker->current->pathCount > 1) {
        index = tracker->driverId;
    }
    tracker->previous = tracker->current;
    tracker->current = ((StateNode **)tracker->current)[index];
    if (data_021557dc[tracker->current->pathValue->f4]
        != driver->animationHolder->animation->animation) {
        DriverContext_UpdateCharacterAnimation(
            driver, data_021557dc[tracker->current->pathValue->f4], 1);
    }
    VecFx32_Subtract(tracker->current->position, tracker->previous->position,
                     &tracker->direction);
    Vector3_MaybeNormalize(&tracker->direction, &tracker->direction);
}
