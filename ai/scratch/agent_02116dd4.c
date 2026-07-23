// PURPOSE: Loads graphics resources and stores their setup information.
// The heap supplies the shared resource block, while the remaining arguments
// are saved as configuration values.  It probably prepares menu graphics.

typedef struct ResourceSetup {
    void *characterGraphics;
    void *cellBank;
    void *palette;
    void *sourceBuffer;
    void *arg1;
    void *arg2;
    void *arg3;
    unsigned short arg4;
    void *arg5;
    unsigned short state;
    unsigned int mode;
} ResourceSetup;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsRelative(void *dst, void *src);
extern void func_020b48b4(void *dst, void *src);
extern void Gfx_ReadPaletteRelative(void *dst, void *src);

extern ResourceSetup *data_0217d354;
extern void *data_0216d4c4;
extern void *data_0216d4bc;
extern void *data_0216d4c0;
extern void *data_0216d4c8;

void func_02116dd4(void *heap, void *arg1, void *arg2, void *arg3,
                    unsigned short arg4, void *arg5)
{
    data_0217d354 = Mem_AllocateHeap(heap, 0x2c);
    Gfx_ReadCharGraphicsRelative(data_0217d354,
                                 find_buf_fn_from_thumb(data_0216d4c4));
    func_020b48b4(&data_0217d354->cellBank,
                  find_buf_fn_from_thumb(data_0216d4bc));
    Gfx_ReadPaletteRelative(&data_0217d354->palette,
                            find_buf_fn_from_thumb(data_0216d4c0));
    data_0217d354->sourceBuffer = find_buf_fn_from_thumb(data_0216d4c8);
    data_0217d354->arg1 = arg1;
    data_0217d354->arg2 = arg2;
    data_0217d354->arg3 = arg3;
    data_0217d354->arg4 = arg4;
    data_0217d354->arg5 = arg5;
    data_0217d354->state = 2;
    data_0217d354->mode = 3;
}
