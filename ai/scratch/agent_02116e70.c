// PURPOSE: Loads the shared waiting-screen graphics resources.
// This function takes no arguments and decodes three already-buffered files.
// The temporary handles are discarded, so it probably verifies the resources.

extern void *find_buf_fn_from_thumb(void *path);
extern void LoadCellBankFrom(void *dst, void *src);
extern void Gfx_ReadCharGraphics(void *dst, void *src);
extern void Gfx_ReadPalette(void *dst, void *src);

extern void *data_0216d4bc;
extern void *data_0216d4c0;
extern void *data_0216d4c4;

void VerifyCommonWaitFiles_from_thumb(void)
{
    void *cell_bank = 0;
    void *char_graphics = 0;
    void *palette = 0;

    LoadCellBankFrom(&cell_bank, find_buf_fn_from_thumb(data_0216d4c4));
    Gfx_ReadCharGraphics(&char_graphics, find_buf_fn_from_thumb(data_0216d4bc));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_0216d4c0));
}
