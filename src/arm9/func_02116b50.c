// PURPOSE: Writes a number as one or two display digits.
// The value and destination character buffer are supplied by the caller.
// Values below ten probably receive a leading zero.

typedef unsigned short u16;
typedef unsigned int u32;

extern void FormatIntegerInString16_from_thumb(u32 value, u16 *dst);

void func_02116b50(u32 value, u16 *dst)
{
    if (value >= 10) {
        FormatIntegerInString16_from_thumb(value, dst);
    } else {
        FormatIntegerInString16_from_thumb(0, dst);
        FormatIntegerInString16_from_thumb(value, dst + 1);
    }
}
