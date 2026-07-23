// PURPOSE: Checks whether the given character appears in the active text.
// The character is supplied by the caller.
// The active wide-text pointer is probably stored in the global state.

extern unsigned short *data_0217b23c[];
extern unsigned short *wcschr(const unsigned short *text, unsigned short character);

int func_020aa5d8(unsigned short character)
{
    return wcschr(data_0217b23c[1], character) != 0;
}
