// PURPOSE: Creates a sprite canvas for one-dimensional two-byte glyphs.
// The first two arguments provide the canvas and its tile storage.
// Width and height choose the probably matching hardware sprite dimensions.
// The final argument is forwarded with the two-byte drawing callbacks.

typedef unsigned char u8;

typedef struct G2d_SpriteSize {
    u8 width;
    u8 height;
} G2d_SpriteSize;

extern G2d_SpriteSize data_021530f8[4][4];
extern void G2d_Sprite_DrawGlyph2(void);
extern void G2d_Sprite_Clear(void);
extern void G2d_Sprite_ClearArea2(void);
extern void G2d_Sprite_CreateImpl(void *sprite, void *tiles, int width, int height,
                                  int extra, void (*draw)(void),
                                  void (*clear)(void),
                                  void (*clearArea)(void),
                                  G2d_SpriteSize size);

void G2d_Sprite_CreateFrom2(void *sprite, void *tiles, int width, int height,
                            int extra)
{
    int widthIndex;
    int heightIndex;
    int scratch;
    G2d_SpriteSize size;

    __asm {
        cmp width, #8
        movlt scratch, width
        movge widthIndex, #3
        clzlt scratch, scratch
        rsblt widthIndex, scratch, #31
        cmp height, #8
        movlt scratch, height
        movge heightIndex, #3
        clzlt scratch, scratch
        rsblt heightIndex, scratch, #31
    }

    size.width = data_021530f8[heightIndex][widthIndex].width;
    size.height = data_021530f8[heightIndex][widthIndex].height;

    G2d_Sprite_CreateImpl(sprite, tiles, width, height, extra,
                          G2d_Sprite_DrawGlyph2, G2d_Sprite_Clear,
                          G2d_Sprite_ClearArea2, size);
}
