// PURPOSE: Measures the size of a multi-line string.
// The output receives the widest line and the total text height.
// The font's line height is combined with the requested line spacing.

typedef struct {
    void *fnif_data;
    int (*next_char_fn_ptr)(void *);
    unsigned short ver_is_old;
    unsigned short char_width_entry_size;
} G2d_Font;

typedef struct {
    int width;
    int height;
} G2dTextSize;

extern int NFTR_GetStringWidth(G2d_Font *font, int charSpacing, void *str,
                               void **outStrEnd);

void G2d_ComputeMaxWidthHeight(G2dTextSize *outSize, G2d_Font *font,
                               int charSpacing, int lineSpacing, void *str)
{
    G2dTextSize size = {0, 0};
    int lineCount = 1;

    if (str != 0) {
        do {
            int width = NFTR_GetStringWidth(font, charSpacing, str, &str);

            if (width > size.width) {
                size.width = width;
            }
            lineCount++;
        } while (str != 0);
    }

    size.height = (lineCount - 1) *
        (lineSpacing + ((signed char *)font->fnif_data)[1]) - lineSpacing;
    *outSize = size;
}
