// PURPOSE: Loads a small set of menu graphics resources.
// The heap argument provides storage for the shared resource record.
// It probably loads character, cell, and palette data into that record.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);
extern void Gfx_ReadPaletteRelative(void *dst, void *src);

extern void *data_0217d37c;
extern void *data_0216e0a8;
extern void *data_0216e0ac;
extern void *data_0216e0b4;
extern void *data_0216e0b0;

void func_0211f2b8(void *heap)
{
    data_0217d37c = Mem_AllocateHeap(heap, 0x10);
    Gfx_ReadCharGraphicsRelative(data_0217d37c, find_buf_fn_from_thumb(data_0216e0a8));
    func_020b48b4((char *)data_0217d37c + 4, find_buf_fn_from_thumb(data_0216e0ac));
    Gfx_ReadPaletteRelative((char *)data_0217d37c + 8, find_buf_fn_from_thumb(data_0216e0b4));
    ((void **)data_0217d37c)[3] = find_buf_fn_from_thumb(data_0216e0b0);
}
