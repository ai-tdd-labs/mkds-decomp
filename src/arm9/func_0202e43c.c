// PURPOSE: Looks up a course value in a four-column table.
// The input probably identifies a course position.
// It divides the position into a row and column, then returns that table entry.

extern long long _s32_div_f(int numerator, int denominator);
extern char data_02154128[];

int func_0202e43c(int value)
{
    long long quotient = _s32_div_f(value, 4);
    long long remainder = _s32_div_f(value, 4);
    return *(int *)(data_02154128 + ((int)quotient << 4) +
                    ((int)(remainder >> 32) << 2));
}
