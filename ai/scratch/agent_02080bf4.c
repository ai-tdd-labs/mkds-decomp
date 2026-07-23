// PURPOSE: Tests whether a point is on the positive side of a direction.
// The first argument probably stores a direction vector at offset 8 and an
// object whose position is at offset 0x18.  The second argument is compared
// against that position when any direction component is nonzero.

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Work {
    void *object;
    int _04;
    VecFx32 direction;
} Work;

typedef struct Object {
    char _00[0x18];
    VecFx32 position;
} Object;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *result);
extern int VecFx32_CrossProduct_0(VecFx32 *a, const VecFx32 *b);

int func_02080bf4(Work *work, const VecFx32 *point)
{
    VecFx32 difference;
    int result = 0;
    Object *object = work->object;

    if (work->direction.x != 0 || work->direction.y != 0 || work->direction.z != 0) {
        VecFx32_Subtract(point, &object->position, &difference);
        if (VecFx32_CrossProduct_0(&work->direction, &difference) > 0) {
            result = 1;
        }
    }

    return result;
}
