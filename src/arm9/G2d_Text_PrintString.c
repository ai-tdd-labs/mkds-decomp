// PURPOSE: Prints a string using a text drawing object.
// The object supplies the text layout settings used to measure the string.
// The alignment flags probably adjust the requested position before drawing.

typedef unsigned int u32;

typedef struct G2dText {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
} G2dText;

typedef struct G2dTextSize {
    int width;
    int height;
} G2dTextSize;

extern void G2d_ComputeMaxWidthHeight(G2dTextSize *size, int unknown_04,
                                      int unknown_08, int unknown_0c,
                                      void *text);
extern void G2d_Text_SomeFn_0(G2dText *textObject, int x, int y, int width,
                              int unknown, int flags, void *text);

void G2d_Text_PrintString(G2dText *textObject, int x, int y, int unknown,
                          int flags, void *text)
{
    // Measure first, because alignment is based on the measured dimensions.
    G2dTextSize size;

    G2d_ComputeMaxWidthHeight(&size, textObject->unknown_04,
                              textObject->unknown_08, textObject->unknown_0c,
                              text);

    if (flags & 0x10) {
        x -= (size.width + 1) / 2;
    } else if (flags & 0x20) {
        x -= size.width;
    }

    if (flags & 2) {
        y -= (size.height + 1) / 2;
    } else if (flags & 4) {
        y -= size.height;
    }

    G2d_Text_SomeFn_0(textObject, x, y, size.width, unknown, flags, text);
}
