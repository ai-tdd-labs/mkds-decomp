// PURPOSE: Draws each line of text with the requested horizontal alignment.
// The text canvas provides the font and the spacing between characters and lines.
// The width and flags select left, centered, or right-aligned drawing.

typedef struct {
    void *fnif_data;
    int (*next_char_fn_ptr)(void *);
    unsigned short ver_is_old;
    unsigned short char_width_entry_size;
} G2d_Font;

typedef struct {
    void *charCanvas;
    G2d_Font *font;
    int charSpacing;
    int lineSpacing;
} G2d_Text;

extern int NFTR_GetStringWidth(G2d_Font *font, int charSpacing, void *str,
                               void **outStrEnd);
extern void G2d_Text_PutChars(G2d_Text *text, int x, int y, int color,
                              void *str, void **outStr);

void G2d_Text_SomeFn_0(G2d_Text *text, int x, int y, int maxWidth,
                       int color, int flags, void *str)
{
    int lineHeight = text->lineSpacing +
        ((signed char *)text->font->fnif_data)[1];
    int halfWidth = (maxWidth + 1) / 2;
    int alignRight = flags & 0x800;
    int alignCenter = flags & 0x400;
    void *cursor = str;

    if (cursor == 0) {
        return;
    }

    do {
        int drawX = x;

        if (alignRight != 0) {
            drawX += maxWidth -
                NFTR_GetStringWidth(text->font, text->charSpacing, cursor, 0);
        } else if (alignCenter != 0) {
            drawX += halfWidth -
                (NFTR_GetStringWidth(text->font, text->charSpacing, cursor, 0) +
                 1) /
                    2;
        }

        G2d_Text_PutChars(text, drawX, y, color, cursor, &cursor);
        y += lineHeight;
    } while (cursor != 0);
}
