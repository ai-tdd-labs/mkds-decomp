// PURPOSE: Copies one ten-byte column into each of four rows.
extern unsigned char *data_0217aa1c;
extern void Mem_CpuCopy8(void *dst, const void *src, unsigned long size);

void func_0205d0e8(int dst_column, int src_column)
{
    int width = 10;
    int src_offset = src_column * width;
    int dst_offset = dst_column * width;
    int row = 0;
    int row_offset = row;

    for (; row < 4; row++, row_offset += 0x50) {
        Mem_CpuCopy8(data_0217aa1c + row_offset + dst_offset,
                     data_0217aa1c + row_offset + src_offset,
                     width);
    }
}
