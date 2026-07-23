// PURPOSE: Returns the current vector value or its length for selected states.
// The object supplies a state through its pointer at offset 0x98.
// States 3 through 5 probably need the length of the vector at offset 0x58.
// All other states return that vector's first component.

typedef int fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char pad_0[8];
    int state;
} StateData;

typedef struct {
    char pad_0[0x58];
    VecFx32 vector;
    char pad_64[0x34];
    StateData *state_data;
} Object;

extern fx32 VecFx32_Norm(const VecFx32 *v);

fx32 func_020d252c(Object *object)
{
    switch (object->state_data->state) {
    case 0:
        goto simple;
    case 1:
        goto simple;
    case 2:
        goto simple;
    case 3:
    case 4:
    case 5:
        goto normalized;
    default:
        goto simple;
    }

normalized:
    return VecFx32_Norm(&object->vector);

simple:
    return object->vector.x;
}
