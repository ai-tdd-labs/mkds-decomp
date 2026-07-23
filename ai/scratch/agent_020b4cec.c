/* PURPOSE: Initializes a fixed-point step state from a divisor.
 * The first argument points to four related fixed-point state values.
 * A zero divisor uses 1.0 directly; otherwise the function stores its reciprocal.
 * The exact role of the two cleared values is uncertain.
 */
typedef int fx32;

typedef struct FxStepState {
    fx32 reciprocal;
    fx32 previousOffset;
    fx32 offset;
    fx32 step;
} FxStepState;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

void func_020b4cec(FxStepState *state, fx32 divisor) {
    state->step = divisor == 0 ? 0x1000 : FX_Div(0x1000, divisor);
    state->reciprocal = state->step;
    state->offset = 0;
    state->previousOffset = state->offset;
}
