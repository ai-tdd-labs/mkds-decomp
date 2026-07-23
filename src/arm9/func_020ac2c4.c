// PURPOSE: Packs pairs of input nibbles into output bytes.
// The first buffer supplies two bytes for every output byte.
// The third argument determines the probably square-sized input span.

typedef unsigned char u8;

extern int _s32_div_f(int dividend, int divisor);

void func_020ac2c4(const u8 *source, u8 *destination, int size)
{
    int i;
    int count = _s32_div_f(size * size, 2);

    i = 0;
    if (i < count) {
        do {
            destination[i] = source[i + i] | (source[i + i + 1] << 4);
            i++;
        } while (i < count);
    }
}
