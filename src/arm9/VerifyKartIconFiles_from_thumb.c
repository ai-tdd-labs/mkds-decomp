// PURPOSE: Verifies that the kart icon graphics files can be loaded.
// This function takes no arguments and decodes temporary graphics handles.
// The handles are discarded, probably to validate the icon resources.

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);

extern void *data_0216d524;
extern void *data_0216d528;
extern void *data_0216d548[];

void VerifyKartIconFiles_from_thumb(void)
{
    void *char_graphics = 0;
    void *cell_bank = 0;
    void *palette = 0;
    int i;

    Gfx_ReadCharGraphicsV2(&char_graphics, find_buf_fn_from_thumb(data_0216d524));
    LoadCellBankFrom(&cell_bank, find_buf_fn_from_thumb(data_0216d528));

    for (i = 0; i < 3; i++) {
        Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_0216d548[i]));
    }
}
