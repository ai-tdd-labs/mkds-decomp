/* PURPOSE: Preloads all graphics files for the WiFi VS course-select
 * screen (sub/bottom variant).
 * No arguments. For each named file it looks up the file buffer by name
 * and parses it into a temporary stack local; the parsed results are
 * discarded here, so this is probably purely a verification/preload
 * pass (called once before the real load elsewhere). Loads: 2x
 * char-graphics (.NCGR, V2 then plain variant), 2x cell banks (.ncer),
 * 4x palettes (.NCLR), 2x screenmaps (.NSCR). */

extern char data_021622f8[]; /* "WiFi_VS_course_select_m_b.NCGR" */
extern char data_02162318[]; /* "WiFi_VS_course_select_s_b.NCGR" */
extern char data_02162338[]; /* "WiFi_VS_course_select_m.nce.ncgr" */
extern char data_0216235c[]; /* "WiFi_VS_course_select_s.nce.ncgr" */
extern char data_02162380[]; /* "WiFi_VS_course_select_m.nce.ncer" */
extern char data_021623a4[]; /* "WiFi_VS_course_select_s.nce.ncer" */
extern char data_021623c8[]; /* "WiFi_VS_course_select_m_b.NCLR" */
extern char data_021623e8[]; /* "WiFi_VS_course_select_m_o.NCLR" */
extern char data_02162408[]; /* "WiFi_VS_course_select_s_b.NCLR" */
extern char data_02162428[]; /* "WiFi_VS_course_select_s_o.NCLR" */
extern char data_02162448[]; /* "WiFi_VS_course_select_m.NSCR" */
extern char data_02162468[]; /* "WiFi_VS_course_select_s.NSCR" */

extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);

void Maybe_WiFi_VS_course_select_s_b(void)
{
    void *chr = 0;  /* sp+0x0: char-graphics result */
    void *pal = 0;  /* sp+0x4: palette result */
    void *cell = 0; /* sp+0x8: cell bank result */
    void *scr = 0;  /* sp+0xc: screenmap result */

    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_021622f8));
    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_02162318));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_02162338));
    Gfx_ReadCharGraphics(&chr, find_buf_fn_from_thumb(data_0216235c));

    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_02162380));
    LoadCellBankFrom(&cell, find_buf_fn_from_thumb(data_021623a4));

    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_021623c8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_021623e8));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02162408));
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_02162428));

    MaybeReadScreenBlock_0(&scr, find_buf_fn_from_thumb(data_02162448));
    MaybeReadScreenBlock_0(&scr, find_buf_fn_from_thumb(data_02162468));
}
