/* Loads/verifies the graphics files of the navigation/"txt_system" context
 * (bottom-screen text system plus select_choises/select_return parts).
 * In mode 2 (download-play, u16 field at 0x027ffc40) only the three base
 * txt_system files are looked up via find_buf_fn_from_thumb; otherwise the
 * full set of 16 files is looked up in the G2L/GE2/... archives. Each buffer
 * is decoded into the same single stack local (sp+0) — return values are
 * ignored, so this probably only validates/preloads the files. */

extern char data_0216e524[]; /* "txt_system_b_00.ncgr" */
extern char data_0216e53c[]; /* "txt_system_bg_00.nscr" */
extern char data_0216e554[]; /* "txt_system_b_00.nclr" */
extern char data_0216e56c[]; /* "txt_system_b_00.ncgr" */
extern char data_0216e584[]; /* "txt_system_b_01.ncgr" */
extern char data_0216e59c[]; /* "txt_system_bg_00.nscr" */
extern char data_0216e5b4[]; /* "txt_system_bg_00_2.nscr" */
extern char data_0216e5cc[]; /* "txt_system_bg_01.nscr" */
extern char data_0216e5e4[]; /* "txt_system_bg_01_2.nscr" */
extern char data_0216e5fc[]; /* "txt_system_bg_02.nscr" */
extern char data_0216e614[]; /* "txt_system_bg_02_2.nscr" */
extern char data_0216e62c[]; /* "txt_system_bg_02_3.nscr" */
extern char data_0216e644[]; /* "txt_system_b_00.nclr" */
extern char data_0216e65c[]; /* "select_choises_s_b.ncgr" */
extern char data_0216e674[]; /* "select_choises_s_bg.nscr" */
extern char data_0216e690[]; /* "select_choises_s_b.nclr" */
extern char data_0216e6a8[]; /* "select_return_s_b_00.ncgr" */
extern char data_0216e6c4[]; /* "select_return_s_bg_00.nscr" */
extern char data_0216e6e0[]; /* "select_return_s_b_00.nclr" */

extern void *find_buf_fn_from_thumb(char *name);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void PrepareNavigationContextFiles_from_thumb(void)
{
    void *out; /* sp+0: single decode-out slot shared by all calls */

    /* 0x027ffc40 is shared-WRAM boot/download-play mode word: direct
     * volatile pointer, never an extern */
    if (*(volatile unsigned short *)0x027ffc40 == 2) {
        /* download-play: only the base txt_system files, other archive */
        Gfx_ReadCharGraphicsV2(&out, find_buf_fn_from_thumb(data_0216e524));
        MaybeReadScreenBlock_0(&out, find_buf_fn_from_thumb(data_0216e53c));
        Gfx_ReadPalette(&out, find_buf_fn_from_thumb(data_0216e554));
    } else {
        Gfx_ReadCharGraphicsV2(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e56c));
        Gfx_ReadCharGraphicsV2(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e584));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e59c));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e5b4));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e5cc));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e5e4));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e5fc));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e614));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e62c));
        Gfx_ReadPalette(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e644));
        Gfx_ReadCharGraphicsV2(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e65c));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e674));
        Gfx_ReadPalette(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e690));
        Gfx_ReadCharGraphicsV2(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e6a8));
        MaybeReadScreenBlock_0(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e6c4));
        Gfx_ReadPalette(&out, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e6e0));
    }
}
