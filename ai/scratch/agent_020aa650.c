// PURPOSE: Maps a wide character to the next non-space character in a cyclic table.

typedef unsigned short u16;

extern u16 *data_02167a04[];
extern u16 *wcschr(const u16 *string, u16 character);
extern int _s32_div_f(int dividend, int divisor);

#pragma optimize_for_size off

u16 func_020aa650(u16 character)
{
    u16 **cursor;
    int table;
    int replacement;
    int offset;
    u16 *found;
    u16 original;

    original = character;

    if (original == 0 || original == 0x3000) {
        return original;
    }

    table = 0;
    cursor = data_02167a04;
    while (table < 4) {
        found = wcschr(*cursor, original);
        if (found != 0) {
            offset = _s32_div_f((int)found - (int)data_02167a04[table], 2);
            break;
        }
        cursor++;
        table++;
    }

    if (table >= 4) {
        goto not_found;
    }

    replacement = 1;
    offset <<= 1;
    while (replacement < 4) {
        u16 *text = data_02167a04[_s32_div_f(table + replacement, 4)];

        if (*(u16 *)(offset + (int)text) == 0x3000) {
            replacement++;
        } else {
            return *(u16 *)((int)text + offset);
        }
    }

not_found:
    return original;
}
