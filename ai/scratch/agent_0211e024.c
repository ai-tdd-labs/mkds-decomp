// PURPOSE: Checks that the cup mark graphics files can be loaded.
// This function takes no arguments and creates temporary resource handles.
// It probably validates the character graphics, cell bank, and palette files.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *src);
extern void LoadCellBankFrom(void *dst, void *src);
extern void Gfx_ReadPalette(void *dst, void *src);

extern void *data_0216dedc;
extern void *data_0216decc;
extern void *data_0216dee0;

void VerifyCupMarkFiles_from_thumb(void)
{
    void *chr = 0;
    void *cell = 0;
    void *pal = 0;

    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_0216dedc));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216decc));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216dee0));
}
