// PURPOSE: Updates a moving object's position and low-height state.
// The argument is probably a moving object's frame state.
// It changes rotation, applies vertical acceleration, and advances position.
// When the object is below its configured height, it sets two state fields.

typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int f0;
    VecFx32 position;
    VecFx32 velocity;
    char pad1c[0x90 - 0x1c];
    u16 field90;
    u16 field92;
    char pad94[0xa0 - 0x94];
    int heightLimit;
    int verticalAcceleration;
    int rotationDirection;
    u16 rotation;
    u16 rotationStep;
} MovingObject;

extern void VecFx32_Add(VecFx32 *dst, VecFx32 *a, VecFx32 *b);

void func_020ec490(MovingObject *object)
{
    if (object->rotationDirection != 0)
        object->rotation += object->rotationStep;
    else
        object->rotation -= object->rotationStep;

    object->velocity.y -= object->verticalAcceleration;
    VecFx32_Add(&object->position, &object->velocity, &object->position);

    if (object->position.y < object->heightLimit) {
        object->field90 = 2;
        object->field92 = 1;
    }
}
