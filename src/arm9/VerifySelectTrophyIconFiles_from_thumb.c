// PURPOSE: Loads the selected trophy icon resources.
// This function takes no arguments and stores temporary decoded resource handles.
// The handles are discarded after the graphics, cell data, and palette are probably verified.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);

extern void *data_0216e0a8;
extern void *data_0216e0ac;
extern void *data_0216e0b4;

void VerifySelectTrophyIconFiles_from_thumb(void)
{
    void *char_graphics = 0;
    void *cell_bank = 0;
    void *palette = 0;

    Gfx_ReadCharGraphicsV2(&char_graphics, find_buf_fn_from_thumb(data_0216e0a8));
    LoadCellBankFrom(&cell_bank, find_buf_fn_from_thumb(data_0216e0ac));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_0216e0b4));
}
