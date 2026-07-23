// PURPOSE: Creates a sprite that draws from tile graphics.
// Takes sprite data, tile data, a mode, an option, and one extra tile argument.
// It probably forwards these values with the standard sprite callbacks.

extern void G2d_Sprite_DrawGlyph(void);
extern void G2d_Sprite_Clear(void);
extern void G2d_Sprite_ClearArea(void);
extern void G2d_Sprite_CreateImpl(void *sprite, void *tiles, int mode, int option,
                                  int extra, void (*draw)(void),
                                  void (*clear)(void), void (*clear_area)(void),
                                  int callback_mode);

void G2d_Sprite_CreateFromTiles(void *sprite, void *tiles, int mode, int option,
                                int extra)
{
    G2d_Sprite_CreateImpl(sprite, tiles, mode, option, extra,
                          G2d_Sprite_DrawGlyph, G2d_Sprite_Clear,
                          G2d_Sprite_ClearArea, mode);
}
