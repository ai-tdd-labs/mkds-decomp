// PURPOSE: Checks which side of a tracked direction a point lies on.
// The tracker contains an object position and a three-component direction.
// It probably returns true when the point is on the direction's positive side.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad00[0x20];
    VecFx32 *position;
} TrackedObject;

typedef struct {
    TrackedObject *object;
    TrackedObject *previous;
    VecFx32 direction;
} DirectionTracker;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *result);
extern int VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);

int func_02080dbc(DirectionTracker *tracker, const VecFx32 *point)
{
    VecFx32 delta;
    int isPositive = 0;

    if (tracker->direction.x != 0 ||
        tracker->direction.y != 0 ||
        tracker->direction.z != 0) {
        VecFx32_Subtract(point, tracker->object->position, &delta);
        if (VecFx32_CrossProduct_0(&tracker->direction, &delta) > 0) {
            isPositive = 1;
        }
    }

    return isPositive;
}
