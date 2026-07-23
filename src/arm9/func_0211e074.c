// PURPOSE: Loads the graphics resources for a menu screen.
// It looks up three already-loaded files and parses them into temporary handles.
// The handles are discarded, probably to validate the resource files.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);

extern void *data_0216ded4;
extern void *data_0216ded8;
extern void *data_0216dec4;

void func_0211e074(void)
{
    void *chr = 0;
    void *cell = 0;
    void *pal = 0;

    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_0216ded4));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216ded8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216dec4));
}
