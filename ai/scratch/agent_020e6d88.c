/* PURPOSE: Builds and normalizes a direction vector.
 * The argument supplies one of the two input vectors.
 * A second vector probably comes from another shared course or camera state.
 * The cross-product result is stored in shared state and normalized in place.
 */

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

extern DirectionState *data_0217b84c;
extern DirectionState *data_0217b860;

extern void Vector3_Cross(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

void func_020e6d88(const VecFx32 *input) {
    DirectionState *state = data_0217b84c;

    state->input = *input;
    state->reference = data_0217b860->reference;
    Vector3_Cross(&state->input, &state->reference, &state->direction);
    Vector3_MaybeNormalize(&data_0217b84c->direction,
                           &data_0217b84c->direction);
}
