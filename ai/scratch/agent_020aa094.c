// PURPOSE: Checks paired wide strings for a character that is absent from its counterpart.

typedef unsigned short u16;

extern u16 *wcschr(const u16 *string, u16 character);
extern int _s32_div_f(int numerator, int denominator);

u16 func_020aa094(u16 **strings, u16 character)
{
    u16 **cursor;
    int i;
    u16 *found;

    cursor = strings;
    for (i = 0; i < 2; i++, cursor++) {
        found = wcschr(*cursor, character);
        if (found != 0) {
            if (strings[1 - i][_s32_div_f((int)found - (int)strings[i], 2)] == 0x3000) {
                return character;
            }
        }
    }
    return character;
}
