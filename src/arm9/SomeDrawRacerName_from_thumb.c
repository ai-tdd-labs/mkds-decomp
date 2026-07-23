// PURPOSE: Draws the formatted name for one racer.
// It builds a temporary text canvas over the name-tile buffer, prints the
// name with a small shadow, and flushes the updated tiles.  The racer id is
// the only argument; the exact text rendering settings are probably UI data.

typedef unsigned short u16;

#pragma optimize_for_size on

extern void *GetLoadedFont_from_thumb(int font_index);
extern u16 *GetSomeBgCanvasTileData_from_thumb(void);
extern void Clear1A44SomeTileData_from_thumb(void);
extern void G2d_Sprite_CreateFromTiles(void *sprite, void *tiles, int mode,
                                       int option, int extra);
extern void G2d_Text_Create(void *canvas, void *sprite, void *font, int mode,
                            int option);
extern void FormatRacerNameString_from_thumb(int racer_id, u16 *destination,
                                             int language);
extern void G2d_TextCanvas_PrintString2(void *canvas, int x, int y, int mode,
                                        int color, void *string);
extern void Arm_FlushRange(void *address, int size);

void SomeDrawRacerName_from_thumb(int racer_id)
{
    unsigned char sprite[0x20];
    unsigned char canvas[0x10];
    u16 name[20];
    void *font;
    u16 *tiles;
    int i;
    int shadow_color;

    font = GetLoadedFont_from_thumb(0);
    tiles = GetSomeBgCanvasTileData_from_thumb();
    Clear1A44SomeTileData_from_thumb();

    for (i = 0; i < 0x100; i++) {
        *(u16 *)((char *)tiles + ((unsigned int)i << 1)) = 0;
    }

    G2d_Sprite_CreateFromTiles(sprite, tiles, 8, 2, 4);
    G2d_Text_Create(canvas, sprite, font, 2, 0);
    FormatRacerNameString_from_thumb(racer_id, name, 0);

    shadow_color = 0x412;
    racer_id = -1;
    for (; racer_id < 2; racer_id++) {
        int j = -1;

        for (; j < 2; j++) {
            G2d_TextCanvas_PrintString2(canvas, racer_id + 0x20, j + 8, 2,
                                         shadow_color, name);
        }
    }

    G2d_TextCanvas_PrintString2(canvas, 0x20, 8, 1, shadow_color, name);
    Arm_FlushRange(GetSomeBgCanvasTileData_from_thumb(), 0x200);
}
