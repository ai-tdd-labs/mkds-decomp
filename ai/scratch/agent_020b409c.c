/* Loads the MA2 content (license card/emblem editor?) once mount entry 1
 * is loaded: three NFTR fonts (LC_Font_s/m, marioFont) are parsed and
 * their addresses stored in a font table (data_0217b390); then, for
 * player characters M and L, the palettes (NCLR), char-graphics (NCGR),
 * cell banks (NCER) and bncl layout buffers are loaded. Probably init of
 * the character-select/license screen. No arguments, no return value. */

extern int IsMountEntryLoaded_from_thumb(int idx);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(const char *name);
extern void NFTR_Load(void *font, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);

/* file names (pool strings, do NOT repeat as literals) */
extern char data_02168454[]; /* "LC_Font_s.NFTR" */
extern char data_02168464[]; /* "LC_Font_m.NFTR" */
extern char data_02168474[]; /* "marioFont.NFTR" */
extern char data_02168484[]; /* "player_character_M_o.NCLR" */
extern char data_021684a0[]; /* "player_character_M_shyguy_o.NCLR" */
extern char data_021684c4[]; /* "player_character_M.nce.ncgr" */
extern char data_021684e0[]; /* "player_character_M.nce.ncer" */
extern char data_021684fc[]; /* "player_character_M.bncl" */
extern char data_02168514[]; /* "player_character_L_o.NCLR" */
extern char data_02168530[]; /* "player_character_L_shyguy_o.NCLR" */
extern char data_02168554[]; /* "player_character_L.nce.ncgr" */
extern char data_02168570[]; /* "player_character_L.nce.ncer" */
extern char data_0216858c[]; /* "player_character_L.bncl" */

/* font objects (each probably 0xc in size, directly after the table) */
extern char data_0217b39c[]; /* LC_Font_s */
extern char data_0217b3a8[]; /* LC_Font_m */
extern char data_0217b3b4[]; /* marioFont */

/* table with pointers to the three fonts */
struct FontTable { void *f0; void *f4; void *f8; };
extern struct FontTable data_0217b390;

/* destination objects for graphics */
extern char data_0217b368[]; /* palette M */
extern char data_0217b388[]; /* palette M shyguy */
extern char data_0217b370[]; /* chars M */
extern char data_0217b378[]; /* cellbank M */
extern char data_0217b36c[]; /* palette L */
extern char data_0217b38c[]; /* palette L shyguy */
extern char data_0217b374[]; /* chars L */
extern char data_0217b37c[]; /* cellbank L */

extern void *data_0217b380[]; /* bncl-buffers: [0]=M, [1]=L */

void LoadMA2ContentIfMounted_from_thumb(void)
{
    if (IsMountEntryLoaded_from_thumb(1)) {
        NFTR_Load(data_0217b39c, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168454));
        NFTR_Load(data_0217b3a8, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168464));
        NFTR_Load(data_0217b3b4, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168474));
        data_0217b390.f0 = data_0217b39c;
        data_0217b390.f4 = data_0217b3a8;
        data_0217b390.f8 = data_0217b3b4;
        Gfx_ReadPalette(data_0217b368, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168484));
        Gfx_ReadPalette(data_0217b388, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021684a0));
        Gfx_ReadCharGraphics(data_0217b370, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021684c4));
        LoadCellBankFrom(data_0217b378, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021684e0));
        data_0217b380[0] = FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021684fc);
        Gfx_ReadPalette(data_0217b36c, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168514));
        Gfx_ReadPalette(data_0217b38c, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168530));
        Gfx_ReadCharGraphics(data_0217b374, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168554));
        LoadCellBankFrom(data_0217b37c, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_02168570));
        data_0217b380[1] = FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216858c);
    }
}
