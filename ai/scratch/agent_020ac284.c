// PURPOSE: Splits packed colour values into separate pixel values.
// The source probably contains two four-bit values in each byte.
// The third argument determines the packed image dimensions.

extern int _s32_div_f(int numerator, int denominator);

void func_020ac284(unsigned char *source, unsigned char *destination, int size)
{
    int i;
    int count = _s32_div_f(size * size, 2);

    for (i = 0; i < count; i++) {
        destination[i * 2] = source[i] & 0xf;
        destination[i * 2 + 1] = (source[i] >> 4) & 0xf;
    }
}
