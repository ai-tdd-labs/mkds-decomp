// PURPOSE: Loads the menu graphics resources into a shared work block.
// The heap argument provides a 12-byte resource record.
// It probably loads character graphics and a related resource into that record.

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);

extern void *data_0217d36c;
extern void *data_0216de54;
extern void *data_0216de58;
extern void *data_0216de50;

void func_0211de40(void *heap)
{
    data_0217d36c = Mem_AllocateHeap(heap, 0xc);
    Gfx_ReadCharGraphicsRelative(data_0217d36c, find_buf_fn_from_thumb(data_0216de54));
    func_020b48b4((char *)data_0217d36c + 4, find_buf_fn_from_thumb(data_0216de58));
    ((void **)data_0217d36c)[2] = find_buf_fn_from_thumb(data_0216de50);
}
