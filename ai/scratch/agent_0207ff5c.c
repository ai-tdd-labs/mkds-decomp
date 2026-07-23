// PURPOSE: Updates a tracker to follow its next object.
// The tracker keeps its old object, advances to the linked object, and stores
// the normalized direction between their vector positions.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct TrackedObject {
    struct TrackedObject *next;
    char padding[0x14];
    VecFx32 *vector;
} TrackedObject;

typedef struct {
    TrackedObject *current;
    TrackedObject *previous;
    VecFx32 direction;
} DirectionTracker;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);

void func_0207ff5c(DirectionTracker *tracker)
{
    tracker->previous = tracker->current;
    tracker->current = tracker->current->next;
    VecFx32_Subtract(tracker->current->vector, tracker->previous->vector,
                     &tracker->direction);
    Vector3_MaybeNormalize(&tracker->direction, &tracker->direction);
}
