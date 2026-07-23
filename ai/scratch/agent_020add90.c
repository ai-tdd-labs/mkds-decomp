// PURPOSE: Gets a character tile index or its default glyph value.
// The font and character select a tile through the font lookup table.
// If no tile exists, the function returns the default glyph value instead.
// The exact meaning of the default field is probably font-specific.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct NFTR_Font {
    void *glyphInfo;
} NFTR_Font;

extern int NFTR_GetTileIndexForCharacter(NFTR_Font *font, u32 character);

int NFTR_SomeFn(NFTR_Font *font, u32 character)
{
    int tileIndex = NFTR_GetTileIndexForCharacter(font, character);

    if (tileIndex == 0xffff) {
        return *(u16 *)((char *)font->glyphInfo + 2);
    }
    return tileIndex;
}
