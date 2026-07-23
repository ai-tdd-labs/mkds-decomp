// PURPOSE: Updates the direction between the current and previous objects.
// Args: tracker stores both object pointers and the resulting direction;
// current is the new current object. The old current object becomes the
// previous one, then their vector fields are subtracted and normalized.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct TrackedObject {
    char pad0[0x18];
    VecFx32 *vector;
} TrackedObject;

typedef struct {
    TrackedObject *current;
    TrackedObject *previous;
    VecFx32 direction;
} DirectionTracker;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *out);

void func_02080adc(DirectionTracker *tracker, TrackedObject *current) {
    tracker->previous = tracker->current;
    tracker->current = current;
    VecFx32_Subtract(tracker->current->vector,
                     tracker->previous->vector,
                     &tracker->direction);
    Vector3_MaybeNormalize(&tracker->direction, &tracker->direction);
}
