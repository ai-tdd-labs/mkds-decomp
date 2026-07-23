// PURPOSE: Draws every racer's name on the race results screen.
// This builds a temporary text renderer over the shared name-tile buffer.
// It lays the names out in two rows and draws a one-pixel shadow first.
// The current racer's colors probably reflect the active race setup.

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TextSprite {
    u32 storage[8];
} TextSprite;

typedef struct TextRenderer {
    TextSprite *sprite;
    void *font;
    int inter_character_width;
    int line_spacing;
} TextRenderer;

extern u8 *gRaceConfig;

extern void *GetLoadedFont_from_thumb(int font_index);
extern u16 *GetSomeBgCanvasTileData_from_thumb(void);
extern void Clear1A44SomeTileData_from_thumb(void);
extern void G2d_Sprite_CreateFromTiles(void *sprite, void *tiles, int width,
                                       int height, int color_mode);
extern void FormatRacerNameString_from_thumb(int racer_id, u16 *destination,
                                             int language);
extern int GetCurrentPlayerRacerId(void);
extern void G2d_Text_PrintString(void *text, int x, int y, int color,
                                 u32 flags, u16 *string);

void DrawRacerNames(void)
{
    TextSprite sprite;
    TextRenderer text;
    u16 name[22];
    void *font;
    u16 *tiles;
    u16 racer;
    int language = 0;
    int color8 = 8;
    int color9 = 9;
    int color10 = 10;
    int color11 = 11;
    int color12 = 12;
    int color13 = 13;
    int color14 = 14;
    int color15 = 15;

    font = GetLoadedFont_from_thumb(0);
    tiles = GetSomeBgCanvasTileData_from_thumb();
    Clear1A44SomeTileData_from_thumb();
    G2d_Sprite_CreateFromTiles(&sprite, tiles, 0x20, 4, 4);

    text.sprite = &sprite;
    text.font = font;
    text.inter_character_width = 1;
    text.line_spacing = 0;

    for (racer = 0; (u32)racer < 8; racer++) {
        int x = (racer % 4) << 6;
        int y = ((u32)racer >> 2) * 0x10 + 8;
        int color;
        int shadow_color;

        FormatRacerNameString_from_thumb(racer, name, language);

        if (racer == GetCurrentPlayerRacerId()) {
            if (((s8 *)gRaceConfig)[0x58] != 0) {
                if (*(int *)(gRaceConfig + racer * 0x30 + 0x74) == 0) {
                    color = color10;
                    shadow_color = color11;
                } else {
                    color = color8;
                    shadow_color = color9;
                }
            } else {
                color = color12;
                shadow_color = color13;
            }
        } else {
            color = color14;
            shadow_color = color15;
        }

        G2d_Text_PrintString(&text, x, y + 1, shadow_color, 0x40a, name);
        G2d_Text_PrintString(&text, x, y, color, 0x40a, name);
    }
}
