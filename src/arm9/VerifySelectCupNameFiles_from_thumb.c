// PURPOSE: Loads the graphics and cell data for the selected cup name.
// This has no arguments and initializes two temporary resource handles.
// The files are probably used to display the selected cup name.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphics(void *dst, void *src);
extern void LoadCellBankFrom(void *dst, void *src);

extern void *data_0216de54;
extern void *data_0216de58;

void VerifySelectCupNameFiles_from_thumb(void)
{
    void *char_graphics = 0;
    void *cell_bank = 0;

    Gfx_ReadCharGraphics(&char_graphics, find_buf_fn_from_thumb(data_0216de54));
    LoadCellBankFrom(&cell_bank, find_buf_fn_from_thumb(data_0216de58));
}
