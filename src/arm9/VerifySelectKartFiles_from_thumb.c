/* PURPOSE: Loads the graphics files for the kart-selection screen.
 * No arguments, no return value. Looks up each "select_kart_s..." file
 * in the already-loaded file buffer set and decodes it into a stack
 * local: char-graphics (sp+0), palette (sp+4), cell bank (sp+8),
 * screen block (sp+0xc). The decoded pointers are thrown away, so this
 * probably only verifies that the files are present/parse correctly.
 * Twin of VerifySelectMenuFiles_from_thumb (0x0202b8d8), minus the
 * download-play branch, plus zero-initialized locals. */

extern char data_02161e64[]; /* "select_kart_s_b.NCGR" */
extern char data_02161e7c[]; /* "select_kart_s.nce.ncgr" */
extern char data_02161e94[]; /* "select_kart_s.nce.ncer" */
extern char data_02161eac[]; /* "select_kart_s_o.NCLR" */
extern char data_02161ec4[]; /* "select_kart_s_b.NCLR" */
extern char data_02161edc[]; /* "select_kart_s.NSCR" */

extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void VerifySelectKartFiles_from_thumb(void)
{
    /* declaration order = stack order sp+0/4/8/0xc; frame is 0x14 due to
     * 8-byte alignment padding (4 pointers = 0x10 + 4 pad) */
    void *chr = 0;   /* sp+0:   char-graphics out */
    void *pal = 0;   /* sp+4:   palette out */
    void *cell = 0;  /* sp+8:   cellbank out */
    void *scrn = 0;  /* sp+0xc: screenblock out */

    /* nested call: FindFileBuffer result goes straight into r1 */
    Gfx_ReadCharGraphicsV2(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161e64));
    Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161e7c));
    LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161e94));
    Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161eac));
    Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161ec4));
    MaybeReadScreenBlock_0(&scrn, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161edc));
}
