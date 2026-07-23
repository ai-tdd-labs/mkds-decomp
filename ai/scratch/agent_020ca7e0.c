// PURPOSE: Draws a string with the supplied text settings.
// This wrapper forwards all six text-drawing arguments unchanged.
// It probably provides a stable call target for this text renderer.

extern void G2d_Text_PrintString(void *text, int x, int y, int color,
    int flags, unsigned short *str);

void G2d_Text_PrintString5(void *text, int x, int y, int color,
    int flags, unsigned short *str)
{
    G2d_Text_PrintString(text, x, y, color, flags, str);
}
