// PURPOSE: Loads the select-return graphics onto the bottom screen.
// It reads character, screen-map, and palette data, then copies them to video memory.
// The returned value is the remaining graphics offset.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
    u16 width;
    u16 height;
    u16 color_mode;
    u16 screen_format;
    u32 size;
    u16 raw_data[1];
} ScreenData;

typedef struct {
    u32 format;
    u32 extended_palette;
    u32 size;
    void *raw_data;
} PaletteData;

typedef struct {
    u8 reserved[0x10];
    u16 tile_map[0x400];
} SelectReturnGraphics;

extern char data_0216e88c[];
extern char data_0216e8a8[];
extern char data_0216e8c4[];
extern SelectReturnGraphics *data_0217d3f8;

extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void MaybeReadCharBlock_1(CharacterData **out, void *buffer);
extern void MaybeReadScreenBlock(ScreenData **out, void *buffer);
extern void Gfx_ReadPaletteRelative(PaletteData **out, void *buffer);
extern void Arm_FlushRange(void *data, u32 size);
extern void CopyBgData_Bg2_Bottom(void *src, u32 offset, u32 size);
extern void TEQSub_Fn26Impl_Fn28Impl(void *src, u32 offset, u32 size);
extern void CopyPaletteBottom(void *src, u32 offset, u32 size);

int LoadSelectReturnGraphics_from_thumb(int offset)
{
    int row_index;
    int column_index;
    CharacterData *character_data;
    ScreenData *screen_data;
    PaletteData *palette_data;
    int row;
    int tile_base;

    MaybeReadCharBlock_1(&character_data, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e88c));
    MaybeReadScreenBlock(&screen_data, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e8a8));
    Gfx_ReadPaletteRelative(&palette_data, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e8c4));

    offset -= character_data->size;
    Arm_FlushRange(character_data->raw_data, character_data->size);
    CopyBgData_Bg2_Bottom(character_data->raw_data, offset, character_data->size);

    for (row_index = 0, row = 0; row_index < 0x20; row_index++) {
        tile_base = offset >> 5;
        for (column_index = 0; column_index < 0x20; column_index++) {
            *(u16 *)(column_index * 2 + (((u32)row << 1) + (u32)data_0217d3f8->tile_map)) =
                tile_base + *(u16 *)((((u32)row << 1) + (u32)screen_data->raw_data) + column_index * 2);
        }
        row += 0x20;
    }

    Arm_FlushRange(data_0217d3f8->tile_map, screen_data->size);
    TEQSub_Fn26Impl_Fn28Impl(data_0217d3f8->tile_map, 0, screen_data->size);
    Arm_FlushRange(palette_data->raw_data, 0x180);
    CopyPaletteBottom((u8 *)palette_data->raw_data + 0x180, 0x180, 0x40);

    return offset;
}
