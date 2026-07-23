// PURPOSE: Fills the tile buffer using dimensions from the supplied layout.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputHeader {
    u16 row_count;
    u16 column_count;
} InputHeader;

typedef struct InputContext {
    u8 _00[4];
    InputHeader *header;
} InputContext;

typedef struct InputOwner {
    u8 _00[0x2C];
    InputContext *context;
} InputOwner;

typedef struct TileBuffer {
    u8 _00[0x0C];
    u16 *entries;
    u32 width;
    u32 row_stride;
    u32 tile_value;
    u32 base_offset;
} TileBuffer;

extern TileBuffer data_0217b254;
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern int _s32_div_f(int numerator, int denominator);

void func_020aafa8(InputOwner *owner)
{
    int row;
    int row_count;
    int column_count;
    int offset;
    int column;
    int index;
    volatile u16 fill_value;
    InputContext *context;
    InputHeader *header;

    context = owner->context;
    header = context->header;
    column_count = header->column_count;
    row_count = header->row_count;
    fill_value = row_count * column_count;
    Mem_CpuFill16(fill_value, data_0217b254.entries,
        (data_0217b254.width << 1) * data_0217b254.row_stride);

    row = 0;
    offset = 0;
    column = 0;
    for (; row < row_count; row++) {
        for (; column < column_count; column++) {
            index = _s32_div_f(row * data_0217b254.row_stride, 2);
            data_0217b254.entries[column + index] =
                (data_0217b254.tile_value << 12) |
                (data_0217b254.base_offset + offset + column);
        }
        offset += column_count;
    }
}
