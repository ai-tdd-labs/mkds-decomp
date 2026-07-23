// PURPOSE: Checks whether a wide character occurs in the current text.
// The argument is the wide character to search for.
// It probably checks a text buffer stored in the current UI state.

typedef unsigned short u16;

extern u16 *data_0217b24c[];
extern u16 *wcschr(const u16 *string, u16 character);

int func_020aa628(u16 character)
{
    return wcschr(data_0217b24c[1], character) != 0;
}
