// PURPOSE: Gets the raw text pointer for a message number.
// Loads the relevant BMG message data, then finds the selected string.
// The message number is probably converted through a ROM-specific table.

typedef unsigned char u8;

extern void Bmg_Load_from_thumb(void *bmg, int messageId);
extern long long _s32_div_f(int value, int divisor);
extern u8 *data_0217b364;
extern u8 *data_0217b360;

void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int messageId)
{
    long long division;

    Bmg_Load_from_thumb(bmg, messageId);
    division = _s32_div_f(messageId, 0x10000);

    return data_0217b364 + 8 +
           *(int *)(data_0217b360 + ((int)(division >> 32) << 2) + 0x10);
}
