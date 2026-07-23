// PURPOSE: Loads the text system graphics onto both Nintendo DS screens.
// The argument is the remaining background character-memory offset.
// It loads character, screen-map, and palette files into the shared context.
// It returns the offset left after any bottom-screen character allocations.

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
    u32 format;
    u32 extended_palette;
    u32 size;
    void *raw_data;
} PaletteData;

typedef struct {
    u8 padding_00[0x44];
    int use_second_character_set;
    int copy_first_characters_to_bottom;
    int copy_second_character_base;
} TextSystemContext;

extern char data_0216e708[];
extern char data_0216e720[];
extern char data_0216e738[];
extern char data_0216e750[];
extern char data_0216e768[];
extern char data_0216e780[];
extern char data_0216e798[];
extern char data_0216e7b0[];
extern char data_0216e7c8[];
extern char data_0216e7e0[];
extern char data_0216e7f8[];
extern char data_0216e810[];
extern char data_0216e828[];

extern TextSystemContext *data_0217d3f0;

extern void *find_buf_fn_from_thumb(char *name);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
    char *name);
extern void MaybeReadCharBlock_1(void **output, void *buffer);
extern void MaybeReadScreenBlock(void **output, void *buffer);
extern void Gfx_ReadPaletteRelative(void **output, void *buffer);
extern void Arm_FlushRange(void *data, u32 size);
extern void CopyBgData_Bg2_Top(void *src, u32 offset, u32 size);
extern void CopyBgData_Bg0_Bottom(void *src, u32 offset, u32 size);
extern void CopyPaletteTop(void *src, u32 offset, u32 size);
extern void CopyPaletteBottom(void *src, u32 offset, u32 size);
extern void *func_0214a214(void);
extern void *GetAnotherSubEngineBGOffset(void);
extern void Mem_CpuFastMemorySet(u32 value, void *destination, u32 size);
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);

#define CONTEXT_U32(offset) \
    (*(u32 *)((u8 *)data_0217d3f0 + (offset)))
#define CONTEXT_U16(offset) \
    (*(u16 *)((u8 *)data_0217d3f0 + (offset)))
#define CONTEXT_OUTPUT(offset) \
    ((void **)((u8 *)data_0217d3f0 + (offset)))

int TextSystemContext_LoadGraphics_from_thumb(int graphics_offset)
{
    volatile u16 bottom_fill;
    CharacterData *first_characters;
    CharacterData *second_characters;
    PaletteData *palette;
    volatile u32 clear_value;

    if (*(volatile u16 *)0x027ffc40 == 2) {
        MaybeReadCharBlock_1(
            (void **)&first_characters,
            find_buf_fn_from_thumb(data_0216e708));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x225c),
            find_buf_fn_from_thumb(data_0216e720));
        Gfx_ReadPaletteRelative(
            (void **)&palette,
            find_buf_fn_from_thumb(data_0216e738));
    } else {
        MaybeReadCharBlock_1(
            (void **)&first_characters,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e750));
        MaybeReadCharBlock_1(
            (void **)&second_characters,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e768));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x225c),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e780));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x2260),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e798));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x2264),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e7b0));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x2268),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e7c8));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x226c),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e7e0));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x2270),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e7f8));
        MaybeReadScreenBlock(
            CONTEXT_OUTPUT(0x2274),
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e810));
        Gfx_ReadPaletteRelative(
            (void **)&palette,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                data_0216e828));
    }

    CONTEXT_U32(0x2220) = 0;

    Arm_FlushRange(first_characters->raw_data, first_characters->size);
    CopyBgData_Bg2_Top(
        first_characters->raw_data, 0, first_characters->size);

    if (data_0217d3f0->copy_first_characters_to_bottom != 0) {
        graphics_offset -= first_characters->size;
        CONTEXT_U32(0x2228) = graphics_offset >> 5;

        Arm_FlushRange(first_characters->raw_data, first_characters->size);
        CopyBgData_Bg0_Bottom(
            first_characters->raw_data,
            graphics_offset,
            first_characters->size);
    }

    if (*(volatile u16 *)0x027ffc40 != 2) {
        int tile_base;

        if (data_0217d3f0->use_second_character_set != 0) {
            CONTEXT_U32(0x2224) = 0;
        }

        CONTEXT_U32(0x223c) = first_characters->size >> 5;

        Arm_FlushRange(second_characters->raw_data, second_characters->size);
        CopyBgData_Bg2_Top(
            second_characters->raw_data,
            CONTEXT_U32(0x223c) << 5,
            second_characters->size);

        if (data_0217d3f0->copy_second_character_base != 0) {
            CONTEXT_U32(0x222c) = CONTEXT_U32(0x2228);
        }

        graphics_offset -= second_characters->size;
        tile_base = graphics_offset >> 5;
        CONTEXT_U32(0x2230) = tile_base;
        CONTEXT_U32(0x2234) = tile_base;
        CONTEXT_U32(0x2238) = tile_base;
        CONTEXT_U32(0x2240) = tile_base;

        Arm_FlushRange(second_characters->raw_data, second_characters->size);
        CopyBgData_Bg0_Bottom(
            second_characters->raw_data,
            graphics_offset,
            second_characters->size);
    }

    Arm_FlushRange(palette->raw_data, 0x1c0);
    CopyPaletteTop(
        (u8 *)palette->raw_data + 0x1c0, 0x1c0, 0x40);
    CopyPaletteBottom(
        (u8 *)palette->raw_data + 0x1c0, 0x1c0, 0x40);

    CONTEXT_U16(0x2244) =
        *(u16 *)((u8 *)palette->raw_data + 0x1dc);
    CONTEXT_U16(0x2246) =
        *(u16 *)((u8 *)palette->raw_data + 0x1be);

    Mem_CpuFastMemorySet(
        clear_value = 0, func_0214a214(), 0x1000);
    Mem_CpuFill16(
        bottom_fill = CONTEXT_U32(0x2230),
        GetAnotherSubEngineBGOffset(),
        0x1000);

    return graphics_offset;
}
