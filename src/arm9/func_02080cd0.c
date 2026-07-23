// PURPOSE: Initializes a direction tracker from an object and its linked object.
// Args: tracker is filled with the two objects and their normalized direction;
// object becomes the first tracked object. The link at object offset 0x0c is
// probably a related or previous object, and the fields at 0x14 and 0x18 are reset.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct TrackedObject {
    char pad00[0x0c];
    struct TrackedObject *linkedObject;
    char pad10[0x08];
    VecFx32 *position;
} TrackedObject;

typedef struct {
    TrackedObject *object;
    TrackedObject *linkedObject;
    VecFx32 direction;
    int counterA;
    int counterB;
} DirectionTracker;

extern const VecFx32 data_021557ec;
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *result);
extern void Vector3_MaybeNormalize(VecFx32 *vector, VecFx32 *result);

void func_02080cd0(DirectionTracker *tracker, TrackedObject *object) {
    tracker->object = object;
    tracker->linkedObject = tracker->object->linkedObject;
    tracker->counterA = 0;
    tracker->counterB = 0;
    tracker->direction = data_021557ec;
    VecFx32_Subtract(tracker->object->position,
                     tracker->linkedObject->position,
                     &tracker->direction);
    Vector3_MaybeNormalize(&tracker->direction, &tracker->direction);
}
