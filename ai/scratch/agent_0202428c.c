// PURPOSE: Aligns and draws a string inside a text rectangle.
// The rectangle position, dimensions, color, flags, and string are provided.
// Vertical alignment probably uses the measured height of the string.

typedef struct G2d_Font G2d_Font;

typedef struct G2d_Text {
    int unknown_00;
    G2d_Font *font;
    int charSpacing;
    int rowSpacing;
} G2d_Text;

extern int NFTR_SomeFn_0(G2d_Font *font, int rowSpacing, void *str);
extern void G2d_Text_SomeFn_0(G2d_Text *text, int x, int y, int width,
                              int color, int flags, void *str);

void G2d_Text_PrintString4(G2d_Text *text, int x, int y, int width,
                           int height, int color, int flags, void *str)
{
    if (flags & 0x100) {
        y += height - NFTR_SomeFn_0(text->font, text->rowSpacing, str);
    } else if (flags & 0x80) {
        int textHeight = NFTR_SomeFn_0(text->font, text->rowSpacing, str);
        y += (height + 1) / 2 - (textHeight + 1) / 2;
    }

    G2d_Text_SomeFn_0(text, x, y, width, color, flags, str);
}
