/* Loads/verifies the graphics files of the "select menu" (etc screen).
 * In mode 2 (download-play, field at 0x027ffc40) the "mb/..._download_..."
 * variants are loaded via find_buf_fn_from_thumb; otherwise the normal
 * select_menu_etc files via the G2L/GE2/... lookup. Each buffer is decoded
 * into a stack local: chargfx (sp+0), palette (sp+4), cellbank (sp+8),
 * screenblock (sp+0xc). Return values are ignored (probably a check). */

extern char data_021626d0[]; /* "mb/select_menu_etc_download_m_b.NCGR" */
extern char data_021626f8[]; /* "mb/select_menu_etc_download_m.nce.ncgr" */
extern char data_02162720[]; /* "mb/select_menu_etc_download_m.nce.ncer" */
extern char data_02162748[]; /* "mb/select_menu_etc_download_m_o.NCLR" */
extern char data_02162770[]; /* "mb/select_menu_etc_download_m_b.NCLR" */
extern char data_02162798[]; /* "mb/select_menu_etc_download_m_bg_00.NSCR" */
extern char data_021627c4[]; /* "mb/select_menu_etc_download_m_bg_01.NSCR" */
extern char data_021627f0[]; /* "select_menu_etc_m_b.NCGR" */
extern char data_0216280c[]; /* "select_menu_etc_m.nce.ncgr" */
extern char data_02162828[]; /* "select_menu_etc_title_m.nce.ncgr" */
extern char data_0216284c[]; /* "select_menu_etc_m.nce.ncer" */
extern char data_02162868[]; /* "select_menu_etc_title_m.nce.ncer" */
extern char data_0216288c[]; /* "select_menu_etc_m_o.NCLR" */
extern char data_021628a8[]; /* "select_menu_etc_m_b.NCLR" */
extern char data_021628c4[]; /* "select_menu_etc_m_bg_00.NSCR" */
extern char data_021628e4[]; /* "select_menu_etc_m_bg_01.NSCR" */

extern void *find_buf_fn_from_thumb(char *name);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void VerifySelectMenuFiles_from_thumb(void)
{
    void *chr;      /* sp+0: char-graphics out */
    void *pal;      /* sp+4: palette out */
    void *cell;     /* sp+8: cellbank out */
    int scrn[2];    /* sp+0xc: screenblock out (8 bytes) */

    if (*(volatile unsigned short *)0x027ffc40 == 2) {
        /* download-play variant: mb/-prefixed files */
        Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_021626d0));
        Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_021626f8));
        LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_02162720));
        Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02162748));
        Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02162770));
        MaybeReadScreenBlock_0(scrn, find_buf_fn_from_thumb(data_02162798));
        MaybeReadScreenBlock_0(scrn, find_buf_fn_from_thumb(data_021627c4));
    } else {
        Gfx_ReadCharGraphicsV2(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021627f0));
        Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216280c));
        Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02162828));
        LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216284c));
        LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02162868));
        Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216288c));
        Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021628a8));
        MaybeReadScreenBlock_0(scrn, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021628c4));
        MaybeReadScreenBlock_0(scrn, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021628e4));
    }
}
