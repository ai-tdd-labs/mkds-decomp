/* PURPOSE: Loads the time-attack ghost menu graphics.
 * The function looks up 24 named assets and passes each buffer to its
 * matching graphics decoder. Decoder outputs are temporary stack values,
 * so this probably verifies or preloads the complete ghost-menu asset set.
 */

extern char data_02162f58[]; /* "TimeAttack_ghost_get_m_b.NCGR" */
extern char data_02162f78[]; /* "TimeAttack_ghost_get_s_b.NCGR" */
extern char data_02162f98[]; /* "TimeAttack_ghost_send_m_b.NCGR" */
extern char data_02162fb8[]; /* "TimeAttack_ghost_send_s_b.NCGR" */
extern char data_02162fd8[]; /* "TimeAttack_ghost_get_m.nce.ncgr" */
extern char data_02162ff8[]; /* "TimeAttack_ghost_get_s.nce.ncgr" */
extern char data_02163018[]; /* "TimeAttack_ghost_send_m.nce.ncgr" */
extern char data_0216303c[]; /* "TimeAttack_ghost_send_s.nce.ncgr" */
extern char data_02163060[]; /* "TimeAttack_ghost_get_m.nce.ncer" */
extern char data_02163080[]; /* "TimeAttack_ghost_get_s.nce.ncer" */
extern char data_021630a0[]; /* "TimeAttack_ghost_send_m.nce.ncer" */
extern char data_021630c4[]; /* "TimeAttack_ghost_send_s.nce.ncer" */
extern char data_021630e8[]; /* "TimeAttack_ghost_get_m_b.NCLR" */
extern char data_02163108[]; /* "TimeAttack_ghost_get_m_o.NCLR" */
extern char data_02163128[]; /* "TimeAttack_ghost_get_s_b.NCLR" */
extern char data_02163148[]; /* "TimeAttack_ghost_get_s_o.NCLR" */
extern char data_02163168[]; /* "TimeAttack_ghost_send_m_b.NCLR" */
extern char data_02163188[]; /* "TimeAttack_ghost_send_s_b.NCLR" */
extern char data_021631a8[]; /* "TimeAttack_ghost_send_m_o.NCLR" */
extern char data_021631c8[]; /* "TimeAttack_ghost_send_s_o.NCLR" */
extern char data_021631e8[]; /* "TimeAttack_ghost_get_m.NSCR" */
extern char data_02163204[]; /* "TimeAttack_ghost_get_s.NSCR" */
extern char data_02163220[]; /* "TimeAttack_ghost_send_m.NSCR" */
extern char data_02163240[]; /* "TimeAttack_ghost_send_s.NSCR" */

extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);
extern void func_02117388(void);

void Maybe_TimeAttack_ghost_get_m_b(void)
{
    void *characterGraphics = 0;
    void *palette = 0;
    void *cellBank = 0;
    void *screenBlock = 0;

    Gfx_ReadCharGraphicsV2(&characterGraphics, find_buf_fn_from_thumb(data_02162f58));
    Gfx_ReadCharGraphicsV2(&characterGraphics, find_buf_fn_from_thumb(data_02162f78));
    Gfx_ReadCharGraphicsV2(&characterGraphics, find_buf_fn_from_thumb(data_02162f98));
    Gfx_ReadCharGraphicsV2(&characterGraphics, find_buf_fn_from_thumb(data_02162fb8));

    Gfx_ReadCharGraphics(&characterGraphics, find_buf_fn_from_thumb(data_02162fd8));
    Gfx_ReadCharGraphics(&characterGraphics, find_buf_fn_from_thumb(data_02162ff8));
    Gfx_ReadCharGraphics(&characterGraphics, find_buf_fn_from_thumb(data_02163018));
    Gfx_ReadCharGraphics(&characterGraphics, find_buf_fn_from_thumb(data_0216303c));

    LoadCellBankFrom(&cellBank, find_buf_fn_from_thumb(data_02163060));
    LoadCellBankFrom(&cellBank, find_buf_fn_from_thumb(data_02163080));
    LoadCellBankFrom(&cellBank, find_buf_fn_from_thumb(data_021630a0));
    LoadCellBankFrom(&cellBank, find_buf_fn_from_thumb(data_021630c4));

    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_021630e8));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_02163108));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_02163128));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_02163148));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_02163168));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_02163188));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_021631a8));
    Gfx_ReadPalette(&palette, find_buf_fn_from_thumb(data_021631c8));

    MaybeReadScreenBlock_0(&screenBlock, find_buf_fn_from_thumb(data_021631e8));
    MaybeReadScreenBlock_0(&screenBlock, find_buf_fn_from_thumb(data_02163204));
    MaybeReadScreenBlock_0(&screenBlock, find_buf_fn_from_thumb(data_02163220));
    MaybeReadScreenBlock_0(&screenBlock, find_buf_fn_from_thumb(data_02163240));

    func_02117388();
}
