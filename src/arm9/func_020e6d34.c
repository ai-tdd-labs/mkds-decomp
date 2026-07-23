// PURPOSE: Builds and normalizes a direction vector in the supplied state.
// The first argument provides the input direction.
// A shared state probably supplies the reference direction.
// The cross product is written to and normalized in the supplied state.

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct DirectionState {
    VecFx32 direction;
    VecFx32 input;
    VecFx32 reference;
} DirectionState;

extern DirectionState *data_0217b860;

extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

void func_020e6d34(const VecFx32 *input, DirectionState *state)
{
    state->input = *input;
    state->reference = data_0217b860->reference;
    Vector3_Cross(&state->input, &state->reference, &state->direction);
    Vector3_MaybeNormalize(&state->direction, &state->direction);
}
