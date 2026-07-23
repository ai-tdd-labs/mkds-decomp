// PURPOSE: Replaces a formatting marker in a BMG string with replacement text.
// The first argument supplies replacement UTF-16 text, the second is the input
// BMG string, and the third receives the expanded output. It probably copies
// later formatting commands unchanged after the replacement.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void CopyMemory16(const void *src, void *dest, u32 size);

void MaybeHandleBmgFormatting_from_thumb(volatile u16 *replacement, u16 *input, u16 *output)
{
    u16 *cursor;
    u8 size;
    int count;

    cursor = output;
    count = 0;
    while (*input != 0x1a || ((u8 *)input)[3] != 1 || input[2] != 0xff) {
        *cursor = *input;
        cursor++;
        count++;
        input++;
    }

    input += ((u8 *)input)[2] >> 1;

    while (*replacement != 0) {
        u16 *write = output + count;
        *write++ = *replacement;
        count++;
        replacement++;
    }

    while (*input != 0) {
        if (*input == 0x1a) {
            size = ((u8 *)input)[2];
            CopyMemory16(input, output + count, size);
            input += size >> 1;
            count += size >> 1;
        } else {
            output[count] = *input;
            count++;
            input++;
        }
    }

    output[count] = 0;
}
