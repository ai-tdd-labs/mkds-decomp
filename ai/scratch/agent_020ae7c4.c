// PURPOSE: Splits three numbers into decimal parts.
// The first two inputs are divided by ten and the third by one hundred and ten.
// The output buffer receives the quotient and remainder from each division.

extern long long _s32_div_f(int dividend, int divisor);

void func_020ae7c4(int first, int second, int third, int *parts)
{
    parts[0] = (int)_s32_div_f(first, 10);
    parts[1] = (int)(_s32_div_f(first, 10) >> 32);
    parts[2] = (int)_s32_div_f(second, 10);
    parts[3] = (int)(_s32_div_f(second, 10) >> 32);
    parts[4] = (int)_s32_div_f(third, 100);
    parts[5] = (int)(_s32_div_f(third - parts[4] * 100, 10) >> 32);
    parts[6] = (int)(_s32_div_f(third, 10) >> 32);
}
