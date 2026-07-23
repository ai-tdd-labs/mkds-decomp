// PURPOSE: Starts an interpolation toward a new value.
// The state records the current interpolated value, a target value, and a duration.
// It preserves the current value before resetting progress for the next interpolation.

typedef struct InterpolationState {
    int start;
    int end;
    int current;
    int count;
} InterpolationState;

extern int func_0212f7f8(InterpolationState *state);

void func_0212f834(InterpolationState *state, int end, int count)
{
    state->start = func_0212f7f8(state);
    state->end = end;
    state->count = count;
    state->current = 0;
}
