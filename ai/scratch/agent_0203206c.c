/* PURPOSE: load and decode the common "select game" screen's graphics files.
 * Unless the shared field at 0x027ffc40 is 2 (single-player/no-multi mode),
 * first load the multi-select ("_m") char graphics, cellbank, palettes and
 * screenblocks; then always load the single-select ("_s") char graphics,
 * cellbank and palette. Each buffer is decoded into a stack local: chr
 * (sp+0), pal (sp+4), cell (sp+8), scrn (sp+0xc). Return values ignored. */

extern char data_021639b8[]; /* "common/select_game_m_b.NCGR" */
extern char data_021639d4[]; /* "common/select_game_m.nce.ncgr" */
extern char data_021639f4[]; /* "common/select_game_m.nce.ncer" */
extern char data_02163a14[]; /* "common/select_game_m_b.NCLR" */
extern char data_02163a30[]; /* "common/select_game_m_o.NCLR" */
extern char data_02163a4c[]; /* "common/select_game_m_multi.NSCR" */
extern char data_02163a6c[]; /* "common/select_game_m_single.NSCR" */
extern char data_02163a90[]; /* "common/select_game_s.nce.ncgr" */
extern char data_02163ab0[]; /* "common/select_game_s.nce.ncer" */
extern char data_02163ad0[]; /* "common/select_game_s_o.NCLR" */

extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void VerifyCommonSelectGameFiles_from_thumb(void)
{
    void *chr;      /* sp+0: char-graphics out */
    void *pal;      /* sp+4: palette out */
    void *cell;     /* sp+8: cellbank out */
    int scrn[2];    /* sp+0xc: screenblock out (8 bytes) */

    if (*(volatile unsigned short *)0x027ffc40 != 2) {
        Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_021639b8));
        Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_021639d4));
        LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_021639f4));
        Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02163a14));
        Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02163a30));
        MaybeReadScreenBlock_0(scrn, find_buf_fn_from_thumb(data_02163a4c));
        MaybeReadScreenBlock_0(scrn, find_buf_fn_from_thumb(data_02163a6c));
    }
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_02163a90));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_02163ab0));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02163ad0));
}
