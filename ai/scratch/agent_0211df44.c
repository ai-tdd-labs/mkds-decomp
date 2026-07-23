// PURPOSE: Loads the cup mark graphics resources.
// This function receives the heap used for its temporary resource holder.
// It probably keeps the decoded graphics, cell data, palette, and source buffer together.

typedef struct CupMarkResources {
    void *characterGraphics;
    void *cellBank;
    void *palette;
    void *sourceBuffer;
} CupMarkResources;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);
extern void Gfx_ReadPaletteRelative(void *dst, void *src);

extern CupMarkResources *data_0217d370;
extern void *data_0216dedc;
extern void *data_0216decc;
extern void *data_0216dee0;
extern void *data_0216ded0;

void func_0211df44(void *heap)
{
    data_0217d370 = Mem_AllocateHeap(heap, 0x10);

    Gfx_ReadCharGraphicsRelative(&data_0217d370->characterGraphics,
                                 find_buf_fn_from_thumb(data_0216dedc));
    func_020b48b4(&data_0217d370->cellBank,
                   find_buf_fn_from_thumb(data_0216decc));
    Gfx_ReadPaletteRelative(&data_0217d370->palette,
                            find_buf_fn_from_thumb(data_0216dee0));
    data_0217d370->sourceBuffer = find_buf_fn_from_thumb(data_0216ded0);
}
