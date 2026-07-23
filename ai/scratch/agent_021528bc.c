// PURPOSE: Converts a twelve-digit friend code into a 64-bit number.
// The input is probably an ASCII code with its digits stored in display order.
// Each digit is accumulated from right to left using increasing decimal places.

typedef long long fx64;

extern fx64 Multiply64(fx64 a, fx64 b);

fx64 ConvertFriendCodeTo64_from_thumb(char *friendCode)
{
    char *volatile code = friendCode;
    fx64 volatile value = 0;
    fx64 place = 1;
    int i = 0;
    volatile int highZero = 0;
    volatile int offsetZero = 0;

    for (; i < 12; i++) {
        /* Keep the signed digit conversion and decimal multiplication separate. */
        value += Multiply64(place, (fx64)(code[11 - i + offsetZero] - 0x30));
        place = Multiply64(place, (fx64)(10 + highZero));
    }

    return value;
}
