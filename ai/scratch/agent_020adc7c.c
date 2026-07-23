// PURPOSE: Copies up to ten characters that fit within the name display width.
// The input is a zero-terminated UTF-16 string and the output is cleared first.
// It returns how many characters fit; glyph widths probably include font metrics.

typedef signed char s8;
typedef unsigned int u32;
typedef unsigned short u16;

extern void *GetLoadedFont_from_thumb(int font_index);
extern void DoFill16(u16 *destination, int value, int size);
extern void MaybeGetNftrCodepointPixelSize(void **glyph, void *font, u32 codepoint);

int GetClampedString10LengthForFontIndex0_from_thumb(const u16 *string, u16 *output)
{
    int pixel_width = 0;
    void *font = GetLoadedFont_from_thumb(0);
    int character_index;

    DoFill16(output, 0, 20);

    for (character_index = 0; character_index < 10; character_index++) {
        int byte_offset = character_index * 2;
        const u16 *source_character = string + character_index;
        u16 codepoint = string[character_index];
        void *glyph;
        int glyph_width;

        if (codepoint == 0)
            return character_index;

        MaybeGetNftrCodepointPixelSize(&glyph, font, codepoint);
        glyph_width = ((s8 *)glyph)[2];

        if (pixel_width + glyph_width > 48)
            return character_index;

        pixel_width += glyph_width + 1;
        *(u16 *)((char *)output + byte_offset) = *source_character;
    }

    return 10;
}
