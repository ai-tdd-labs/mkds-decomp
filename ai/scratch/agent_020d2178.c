// PURPOSE: Builds a bit mask for the decimal digits in a number.
// The input is split into thousands, hundreds, tens, and ones.
// Each present digit sets its matching bit in the returned mask.

extern int _s32_div_f(int dividend, int divisor);

int func_020d2178(int value)
{
    int mask = 0;
    short remainder = (short)value;
    int digit;

    if (remainder >= 1000) {
        digit = _s32_div_f(remainder, 1000);
        mask |= 1 << digit;
        remainder = (short)(remainder - (1000 * digit));
    }

    if (remainder >= 100) {
        digit = _s32_div_f(remainder, 100);
        mask |= 1 << digit;
        remainder = (short)(remainder - (100 * digit));
    }

    if (remainder >= 10) {
        digit = _s32_div_f(remainder, 10);
        mask |= 1 << digit;
        remainder = (short)(remainder - (10 * digit));
    }

    if (remainder >= 1) {
        mask |= 1 << remainder;
    }

    return mask;
}
