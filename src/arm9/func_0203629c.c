// PURPOSE: Prints a text string with the supplied display settings.
// Arguments: text object, position, color, flags, and a UTF-16 string.
// Behaviour: forwards every argument unchanged to the text renderer.
// This small wrapper probably exists to provide a stable call target.

extern void G2d_Text_PrintString(void *text, int x, int y, int color,
    unsigned int flags, unsigned short *str);

void func_0203629c(void *text, int x, int y, int color,
    unsigned int flags, unsigned short *str)
{
    G2d_Text_PrintString(text, x, y, color, flags, str);
}
