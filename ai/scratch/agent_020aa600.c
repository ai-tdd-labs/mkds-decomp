// PURPOSE: Checks whether a character appears in the current wide text.
// The argument is the wide character to find.
// The text pointer is probably stored in the global work structure.

typedef unsigned short u16;

extern u16 *data_0217b244[];
extern u16 *wcschr(const u16 *string, u16 character);

int func_020aa600(u16 character)
{
    return wcschr(data_0217b244[1], character) != 0;
}
