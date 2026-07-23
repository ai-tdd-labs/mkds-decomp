// PURPOSE: Loads menu graphics resources into a shared resource block.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);
extern void Gfx_ReadPaletteRelative(void *dst, void *src);

extern void *data_0217d35c;
extern void *data_0216d534;
extern void *data_0216d538;
extern void *data_0216d53c;
extern void *data_0216d52c;

void func_021172a8(void *heap)
{
    int i;

    data_0217d35c = Mem_AllocateHeap(heap, 0x18);
    Gfx_ReadCharGraphicsRelative(data_0217d35c,
                                 find_buf_fn_from_thumb(data_0216d534));
    func_020b48b4((char *)data_0217d35c + 4,
                  find_buf_fn_from_thumb(data_0216d538));
    for (i = 0; i < 3; i++) {
        Gfx_ReadPaletteRelative((char *)data_0217d35c + 8 + i * 4,
                                find_buf_fn_from_thumb(((void **)&data_0216d53c)[i]));
    }
    ((void **)data_0217d35c)[5] = find_buf_fn_from_thumb(data_0216d52c);
}
