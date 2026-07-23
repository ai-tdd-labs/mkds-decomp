// PURPOSE: Formats three numbers as colon-separated decimal digits.
// The output is a zero-terminated string of 16-bit character codes.
// The first two values use two digits, and the final value uses three digits.
typedef unsigned short u16;
typedef unsigned int u32;

void func_02025cd0(u16 *output, u32 first, u32 second, u32 third)
{
    output[0] = (u16)(first / 10 % 10 + 0x30);
    output[1] = (u16)(first % 10 + 0x30);
    output[2] = 0x3a;

    output[3] = (u16)(second / 10 % 10 + 0x30);
    output[4] = (u16)(second % 10 + 0x30);
    output[5] = 0x3a;

    output[6] = (u16)(third / 100 % 10 + 0x30);
    output[7] = (u16)(third / 10 % 10 + 0x30);
    output[8] = (u16)(third % 10 + 0x30);
    output[9] = 0;
}
