// PURPOSE: Loads menu graphics data into a shared resource block.
// The heap argument supplies storage for four resource pointers.
// It probably loads character, cell, and palette data, then stores a final file buffer.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);
extern void Gfx_ReadPaletteRelative(void *dst, void *src);

extern void *data_0217d370;
extern void *data_0216ded4;
extern void *data_0216ded8;
extern void *data_0216dec4;
extern void *data_0216dec8;

void func_0211dfb4(void *heap)
{
    data_0217d370 = Mem_AllocateHeap(heap, 0x10);
    Gfx_ReadCharGraphicsRelative(data_0217d370, find_buf_fn_from_thumb(data_0216ded4));
    func_020b48b4((char *)data_0217d370 + 4, find_buf_fn_from_thumb(data_0216ded8));
    Gfx_ReadPaletteRelative((char *)data_0217d370 + 8, find_buf_fn_from_thumb(data_0216dec4));
    ((void **)data_0217d370)[3] = find_buf_fn_from_thumb(data_0216dec8);
}
