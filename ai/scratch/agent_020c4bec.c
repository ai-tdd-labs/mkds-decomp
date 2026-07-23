// PURPOSE: Prepares the graphics and course title shown before a race.
// This allocates the race-intro state and loads its palette, tiles, and cells.
// It draws either the course name or the mission label into the tile data.
// The finished palette and character graphics are uploaded for display.

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 format;
    u32 extended_palette;
    u32 size;
    void *raw_data;
} PaletteData;

typedef struct {
    u16 width;
    u16 height;
    u32 pixel_format;
    u32 mapping_type;
    u32 character_format;
    u32 size;
    void *raw_data;
} CharacterData;

typedef struct {
    u32 reserved_low : 10;
    u32 priority : 2;
    u32 reserved_high : 20;
    u32 second_word;
} RaceIntroOamRecord;

typedef struct {
    int frame_count;
    PaletteData *palette;
    CharacterData *characters;
    void *cells[3];
    RaceIntroOamRecord oam[128];
    u32 unused_tail;
} RaceIntroData;

typedef struct {
    u32 storage[8];
} TextSprite;

typedef struct {
    TextSprite *sprite;
    void *font;
    int inter_character_width;
    int line_spacing;
} TextRenderer;

typedef struct {
    int internal_course_id;
    int cup_index;
    int race_mode;
    u8 padding_0c[0x48];
    s8 mission_level;
} RaceConfig;

extern RaceIntroData *data_0217b3e8;
extern RaceConfig *gRaceConfig;

extern char data_0216962c[];
extern char data_02169644[];
extern char data_0216965c[];
extern char data_02169674[];
extern char data_02169680[];

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *func_020b47c0(char *name);
extern void *func_020b47cc(char *name);
extern void Gfx_ReadPalette(void *destination, void *buffer);
extern void Gfx_ReadCharGraphics(void *destination, void *buffer);
extern void LoadCellBankFrom(void *destination, void *buffer);
extern void *CellBank_GetMetatileEntry(void *cell_bank, u16 index);
extern void *GetLoadedFont_from_thumb(int index);
extern void G2d_Sprite_CreateFromTiles(void *sprite, void *tile_data,
                                       int width, int height, int color_mode);
extern int GetBmgIndexFromCircuitIndex_from_thumb(int internal_course_id);
extern int GetSomeInterCharacterWidth2(void);
extern int GetSomeInterCharacterWidth(void);
extern u16 *Bmg_GetRawStringPointer_from_thumb(void *bmg, int message_id);
extern void G2d_Text_PrintString(void *text, int x, int y, int color,
                                 u32 flags, u16 *string);
extern void Arm_FlushRange(void *address, u32 size);
extern void CopySomePaletteData(void *source, u32 offset, u32 size);
extern void CopyTileDataTop_0(void *source, u32 offset, u32 size);

void InitializeRaceIntroData(void)
{
    void *cell_bank;
    TextSprite sprite;
    TextRenderer text;
    int i;
    int cell_index;
    int message_id = -1;
    void *font;

    data_0217b3e8 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x41c);

    for (i = 0; i < 128; i++) {
        data_0217b3e8->oam[i].priority = 3;
    }

    data_0217b3e8->frame_count = 0;
    Gfx_ReadPalette(&data_0217b3e8->palette,
                    func_020b47c0(data_0216962c));
    Gfx_ReadCharGraphics(&data_0217b3e8->characters,
                         func_020b47c0(data_02169644));
    LoadCellBankFrom((cell_bank = 0, &cell_bank),
                     func_020b47c0(data_0216965c));

    for (cell_index = 0; cell_index < 3; cell_index++) {
        data_0217b3e8->cells[cell_index] =
            CellBank_GetMetatileEntry(cell_bank, (u16)cell_index);
    }

    font = GetLoadedFont_from_thumb(2);
    G2d_Sprite_CreateFromTiles(&sprite,
                               data_0217b3e8->characters->raw_data,
                               0x20, 4, 4);

    text.sprite = &sprite;
    text.font = font;
    text.inter_character_width = 1;
    text.line_spacing = 0;

    if (gRaceConfig->race_mode == 0) {
        message_id = GetBmgIndexFromCircuitIndex_from_thumb(
            gRaceConfig->internal_course_id);
        text.inter_character_width = GetSomeInterCharacterWidth2();
    } else if (gRaceConfig->race_mode == 4) {
        message_id = (gRaceConfig->race_mode == 4
                          ? gRaceConfig->mission_level
                          : message_id) + 0x55;
        text.inter_character_width = GetSomeInterCharacterWidth();
    }

    G2d_Text_PrintString(
        &text, 0, 9, 0xe, 0x40a,
        Bmg_GetRawStringPointer_from_thumb(func_020b47cc(data_02169674),
                                           message_id));
    G2d_Text_PrintString(
        &text, 0, 8, 0xe, 0x40a,
        Bmg_GetRawStringPointer_from_thumb(func_020b47cc(data_02169680),
                                           message_id));

    Arm_FlushRange(data_0217b3e8->characters->raw_data,
                   data_0217b3e8->characters->size);
    CopySomePaletteData(data_0217b3e8->palette->raw_data, 0,
                        data_0217b3e8->palette->size);
    CopyTileDataTop_0(data_0217b3e8->characters->raw_data, 0,
                      data_0217b3e8->characters->size);
}
