// PURPOSE: Gets the font metrics for a character codepoint.
// The output receives values selected by the font and the supplied character.
// It probably resolves a fallback glyph before storing the metrics.

typedef unsigned int u32;

typedef struct NFTR_Font {
    void *glyphInfo;
} NFTR_Font;

extern int NFTR_SomeFn(NFTR_Font *font, u32 character);
extern void func_020add18(int *output, NFTR_Font *font, int index);

void MaybeGetNftrCodepointPixelSize(int *output, NFTR_Font *font, u32 character)
{
    func_020add18(output, font, NFTR_SomeFn(font, character));
}
