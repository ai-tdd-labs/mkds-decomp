/* PURPOSE: Loads the graphics files for the character-selection screen.
 * No arguments, no return value. Looks up each "select_character_..." file
 * (grand-prix and single variants, plus name/title overlays) in the
 * already-loaded file buffer set and decodes it into a stack local:
 * char-graphics (sp+0), palette (sp+4), cell bank (sp+8). The decoded
 * pointers are thrown away, so this probably only verifies that the
 * files are present/parse correctly.
 * Twin of VerifySelectKartFiles_from_thumb (0x02027df8), without the
 * screen-block loads. */

extern char data_02161b3c[]; /* "select_character_gp_m.nce.ncgr" */
extern char data_02161b5c[]; /* "select_character_gp_m.nce.ncer" */
extern char data_02161b7c[]; /* "select_character_gp_m_o.NCLR" */
extern char data_02161b9c[]; /* "select_character_s.nce.ncgr" */
extern char data_02161bb8[]; /* "select_character_s.nce.ncer" */
extern char data_02161bd4[]; /* "select_character_s_o.NCLR" */
extern char data_02161bf0[]; /* "select_character_gp_name_m.nce.ncgr" */
extern char data_02161c14[]; /* "select_character_gp_name_m.nce.ncer" */
extern char data_02161c38[]; /* "select_character_gp_title_m.nce.ncgr" */
extern char data_02161c60[]; /* "select_character_gp_title_m.nce.ncer" */

extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);

void VerifySelectCharacterFiles_from_thumb(void)
{
    /* declaration order = stack order sp+0/4/8 */
    void *chr = 0;   /* sp+0: char-graphics out */
    void *pal = 0;   /* sp+4: palette out */
    void *cell = 0;  /* sp+8: cellbank out */

    /* nested call: FindFileBuffer result goes straight into r1 */
    Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161b3c));
    LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161b5c));
    Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161b7c));
    Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161b9c));
    LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161bb8));
    Gfx_ReadPalette(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161bd4));
    Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161bf0));
    LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161c14));
    Gfx_ReadCharGraphics(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161c38));
    LoadCellBankFrom(&cell, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02161c60));
}
