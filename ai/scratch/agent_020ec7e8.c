/* PURPOSE: Moves an object and updates its rotation each frame.
 *
 * The argument is probably a moving object's state. This adjusts its 16-bit
 * rotation in the selected direction, applies vertical acceleration, advances
 * its position, and reports whether it is below a configured height.
 */

typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int f0;
    VecFx32 position;          /* +0x04 */
    VecFx32 velocity;          /* +0x10 */
    char pad1c[0xa0 - 0x1c];
    int heightLimit;           /* +0xa0 */
    int verticalAcceleration;  /* +0xa4 */
    int rotationDirection;     /* +0xa8 */
    u16 rotation;              /* +0xac */
    u16 rotationStep;          /* +0xae */
} MovingObject;

extern void VecFx32_Add(VecFx32 *dst, VecFx32 *a, VecFx32 *b);

int func_020ec7e8(MovingObject *object)
{
    if (object->rotationDirection != 0)
        object->rotation += object->rotationStep;
    else
        object->rotation -= object->rotationStep;

    object->velocity.y -= object->verticalAcceleration;
    VecFx32_Add(&object->position, &object->velocity, &object->position);

    return object->position.y < object->heightLimit;
}
