// PURPOSE: Fills a rectangular region inside one 8-by-8 graphics tile.
/*
 * dst points to 4bpp or 8bpp tile data, and x/y/w/h select the region.
 * value contains the repeated pixel bits written into that region.
 * A whole-tile fill uses the fast memory-fill routine.
 */
typedef unsigned int u32;

extern void Mem_CpuFastMemorySet(u32 value, void *dst, u32 size);

void func_02024000(void *dst, int x, int y, int w, int h, u32 value, int bpp)
{
    volatile u32 fill_value;

    if (w == 8 && h == 8) {
        fill_value = value;
        Mem_CpuFastMemorySet(fill_value, dst, bpp << 3);
        return;
    }

    if (bpp == 4) {
        int start = x * 4;
        int end = 32 - (start + w * 4);
        u32 mask = (~0u >> start) << (end + x * 4);
        u32 fill = value & (mask >> end);
        u32 *row = (u32 *)dst + y;
        u32 *row_end = row + h;
        u32 keep = ~(mask >> end);

        while (row < row_end) {
            *row = fill | (*row & keep);
            row++;
        }
    } else {
        u32 start = x * 8;
        u32 end = 64 - (start + w * 8);
        u32 left = ~0u >> start;
        u32 low = end >= 32
                      ? (left << (start + (end - 32) + start - start)) >>
                            (end - 32)
                      : left << start;
        u32 right = ~0u << end;
        u32 high = start >= 32
                       ? (right >> ((start - 32) + end)) << (start - 32)
                       : right >> end;
        u32 high_fill;
        u32 low_fill = value & low;
        u32 *row = (u32 *)dst + y * 2;
        u32 *row_end = row + h * 2;

        high_fill = value & high;
        {
            u32 keep_low = ~low;
            u32 keep_high = ~high;

            while (row < row_end) {
                row[0] = low_fill | (row[0] & keep_low);
                row[1] = high_fill | (row[1] & keep_high);
                row += 2;
            }
        }
    }
}
