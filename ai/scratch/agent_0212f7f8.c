// PURPOSE: Returns the interpolated value for the current step.
// The input probably describes a linear range with a current position and total count.
// A completed range returns its end value directly.

typedef struct InterpolationState {
    int start;
    int end;
    int current;
    int count;
} InterpolationState;

extern int _s32_div_f(int numerator, int denominator);

int func_0212f7f8(InterpolationState *state)
{
    if (state->current >= state->count) {
        return state->end;
    }

    {
        int start = state->start;
        int end = state->end;
        int current = state->current;
        int count = state->count;
        return start + _s32_div_f(current * (end - start), count);
    }
}
