/* Loads/verifies all graphics files of the multi-select screen
 * (member selection): 5x char-graphics (.NCGR), 4x cell banks (.ncer),
 * 5x palettes (.NCLR) and 2x screenmaps (.NSCR). Each step first looks up
 * the file buffer by name and parses it into a temporary stack local;
 * the results are discarded — probably purely a verification/preload. */

extern char data_02163280[]; /* "multi_select_member_s_b.NCGR" */
extern char data_021632a0[]; /* "multi_select_member_m.nce.ncgr" */
extern char data_021632c0[]; /* "multi_select_member_group_s.nce.ncgr" */
extern char data_021632e8[]; /* "multi_select_member_register_s.nce.ncgr" */
extern char data_02163310[]; /* "multi_select_NS_s.nce.ncgr" */
extern char data_0216332c[]; /* "multi_select_member_m.nce.ncer" */
extern char data_0216334c[]; /* "multi_select_member_group_s.nce.ncer" */
extern char data_02163374[]; /* "multi_select_member_register_s.nce.ncer" */
extern char data_0216339c[]; /* "multi_select_NS_s.nce.ncer" */
extern char data_021633b8[]; /* "multi_select_member_m_o.NCLR" */
extern char data_021633d8[]; /* "multi_select_member_s_b.NCLR" */
extern char data_021633f8[]; /* "multi_select_member_group_s_o.NCLR" */
extern char data_0216341c[]; /* "multi_select_member_register_s_o.NCLR" */
extern char data_02163444[]; /* "multi_select_NS_s_o.NCLR" */
extern char data_02163460[]; /* "multi_select_member_s_register.NSCR" */
extern char data_02163484[]; /* "multi_select_member_s_group.NSCR" */

extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void MaybeVerifyMultiSelectFiles_from_thumb(void)
{
    void *chr = 0;  /* sp+0x0: char-graphics result */
    void *pal = 0;  /* sp+0x4: palette result */
    void *cell = 0; /* sp+0x8: cell bank result */
    void *scr = 0;  /* sp+0xc: screenmap result */

    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_02163280));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_021632a0));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_021632c0));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_021632e8));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_02163310));

    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216332c));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216334c));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_02163374));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_0216339c));

    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_021633b8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_021633d8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_021633f8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216341c));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02163444));

    MaybeReadScreenBlock_0(&scr, find_buf_fn_from_thumb(data_02163460));
    MaybeReadScreenBlock_0(&scr, find_buf_fn_from_thumb(data_02163484));
}
