// PURPOSE: Loads the menu graphics resources.
// The function creates temporary handles for character, cell, and palette data.
// The handles are discarded after the resources are probably validated.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *src);
extern void LoadCellBankFrom(void *dst, void *src);
extern void Gfx_ReadPalette(void *dst, void *src);

extern void *data_0216d534[];
extern void *data_0216d538;
extern void *data_0216d53c;

void func_02117388(void)
{
    void *chr = 0;
    void *cell = 0;
    void *pal = 0;
    int i;

    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_0216d534[0]));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216d538));
    for (i = 0; i < 3; i++) {
        Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216d534[i]));
    }
}
