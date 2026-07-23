// PURPOSE: Loads enabled text sprites and updates their animations.
// The argument points to nine enable words, one for each text graphic.
// Static entries copy bounded tile regions into the appropriate screen map.
// The last two entries probably refresh shared animation graphics instead.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 values[9];
} TextGraphicIndices;

typedef struct {
    u8 left;
    u8 right;
    u8 top;
    u8 bottom;
} TextGraphicBounds;

extern const TextGraphicIndices data_0216e6fc;
extern const TextGraphicBounds data_0215d080[];
extern u8 *data_0217d3f0;

extern void Mem_CpuFastMemorySet(u32 value, void *destination, u32 size);
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern void TextSystemContext_UpdateAnimationGraphics_from_thumb(void);

void TextSystemContext_LoadEnabledSpritesAndAnimations_from_thumb(
    u32 *enabled_graphics)
{
    int i;
    u8 *graphic_index_cursor;
    int tile_base_offset;
    volatile u16 sub_fill_value;
    volatile u32 clear_value;
    TextGraphicIndices graphic_indices = data_0216e6fc;

    clear_value = 0;
    Mem_CpuFastMemorySet(clear_value, data_0217d3f0 + 0x54, 0x1000);

    sub_fill_value = *(u32 *)(data_0217d3f0 + 0x2230);
    Mem_CpuFill16(sub_fill_value, data_0217d3f0 + 0x1054, 0x1000);

    for (i = 0, graphic_index_cursor = graphic_indices.values,
             tile_base_offset = i;
         i < 9;
         enabled_graphics++, graphic_index_cursor++, tile_base_offset += 4,
             i++) {
        if (*enabled_graphics != 0) {
            if ((u32)(i - 7) <= 1) {
                TextSystemContext_UpdateAnimationGraphics_from_thumb();
            } else if (i != 6) {
                int graphic_index = *graphic_index_cursor;
                u16 *destination = (u16 *)(data_0217d3f0 + 0x1054);
                const TextGraphicBounds *bounds;
                int graphic_offset;
                int row;
                int row_offset;
                int left;
                int right;
                int column;

                if ((u32)i <= 1) {
                    destination = (u16 *)data_0217d3f0;
                    destination = (u16 *)((u8 *)destination + 0x54);
                }

                graphic_offset = graphic_index << 2;
                bounds = (const TextGraphicBounds *)
                    ((const u8 *)data_0215d080 + graphic_offset);
                row = bounds->top;

                if (row <= bounds->bottom) {
                    row_offset = row << 5;
                    left = bounds->left;
                    right = bounds->right;

                    do {
                        for (column = left; column <= right; column++) {
                            *(u16 *)(column * 2 +
                                (((u32)row_offset << 1) +
                                    (u32)destination)) =
                                *(u32 *)(data_0217d3f0 + tile_base_offset +
                                    0x2220) +
                                *(u16 *)(column * 2 +
                                    (((u32)row_offset << 1) +
                                        (u32)*(u8 **)(data_0217d3f0 +
                                            graphic_offset + 0x225c)) +
                                    0xc);
                        }

                        row_offset += 0x20;
                        row++;
                    } while (row <= bounds->bottom);
                }
            }
        }
    }
}
