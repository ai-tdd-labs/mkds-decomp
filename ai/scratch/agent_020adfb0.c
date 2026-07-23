// PURPOSE: Prints text through a configured text canvas.
// Passes the canvas, string settings, and two trailing stack arguments onward.
// This is probably a thin convenience wrapper around the shared text printer.

extern void G2d_Text_PrintString(void *canvas, int a1, int a2, int a3, int a4, int a5);

void G2d_TextCanvas_PrintString2(void *canvas, int a1, int a2, int a3, int a4, int a5)
{
    G2d_Text_PrintString(canvas, a1, a2, a3, a4, a5);
}
