/* Loads all graphics resources of the small keyboard / 10-key input screen:
 * the bnbl/bncl/bnll layout buffers for both the 10-key and normal keyboard
 * variants are looked up and stored in the context (gKeyboardScreen), the
 * object char/cell/palette (Keyboard_s_o.*) are parsed and uploaded to the
 * top-screen OBJ VRAM/palette, and the bottom-screen background (flame
 * ncgr/nscr/NCLR) is uploaded to BG3. Probably the keyboard screen init.
 * No arguments, no return value. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* file names (pool strings, do NOT repeat as literals) */
extern char data_0216e940[]; /* "Keyboard_s_10key.bnbl" */
extern char data_0216e958[]; /* "Keyboard_s_10key.bncl" */
extern char data_0216e970[]; /* "Keyboard_s_10key.bnll" */
extern char data_0216e988[]; /* "Keyboard_s.bnbl" */
extern char data_0216e998[]; /* "Keyboard_s.bncl" */
extern char data_0216e9a8[]; /* "Keyboard_s.bnll" */
extern char data_0216e9b8[]; /* "Keyboard_s_o.nce.ncgr" */
extern char data_0216e9d0[]; /* "Keyboard_s_o.nce.ncer" */
extern char data_0216e9e8[]; /* "Keyboard_s_o.nclr" */
extern char data_0216e9fc[]; /* "Keyboard_s_b_flame.ncgr" */
extern char data_0216ea14[]; /* "Keyboard_s_b_flame02.nscr" */
extern char data_0216ea30[]; /* "Keyboard_s_b_flame01.nscr" */
extern char data_0216ea4c[]; /* "Keyboard_s_b.NCLR" */

/* char-data block (NNSG2dCharacterData-like): szByte@0x10, pRawData@0x14 */
typedef struct {
    u16 W;              /* 0x00 */
    u16 H;              /* 0x02 */
    u32 pixelFmt;       /* 0x04 */
    u32 mapingType;     /* 0x08 */
    u32 characterFmt;   /* 0x0c */
    u32 szByte;         /* 0x10 */
    void *pRawData;     /* 0x14 */
} CharData;

/* palette block (NNSG2dPaletteData-like): szByte@0x8, pRawData@0xc */
typedef struct {
    u32 fmt;            /* 0x00 */
    u32 bExtendedPlt;   /* 0x04 */
    u32 szByte;         /* 0x08 */
    void *pRawData;     /* 0x0c */
} PaletteData;

/* keyboard-screen context (only the fields this function touches) */
typedef struct {
    u8 pad0[0x90];      /* 0x00 */
    void *cell;         /* 0x90: Keyboard_s_o.nce.ncer cell bank */
    CharData *chr;      /* 0x94: Keyboard_s_o.nce.ncgr char data */
    PaletteData *pal;   /* 0x98: Keyboard_s_o.nclr palette */
    void *bncl_10key;   /* 0x9c: Keyboard_s_10key.bncl */
    void *bncl_s;       /* 0xa0: Keyboard_s.bncl */
    void *bnbl_10key;   /* 0xa4: Keyboard_s_10key.bnbl */
    void *bnbl_s;       /* 0xa8: Keyboard_s.bnbl */
    void *bnll_10key;   /* 0xac: Keyboard_s_10key.bnll */
    void *bnll_s;       /* 0xb0: Keyboard_s.bnll */
    void *scr_flame02;  /* 0xb4: Keyboard_s_b_flame02.nscr screen data */
    void *scr_flame01;  /* 0xb8: Keyboard_s_b_flame01.nscr screen data */
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;

extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphics(void *dst, void *buf);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *buf);
extern void LoadCellBankFrom(void *dst, void *buf);
extern void Gfx_ReadPalette(void *dst, void *buf);
extern void MaybeReadScreenBlock_0(void *dst, void *buf);
extern void Arm_FlushRange(void *ptr, u32 size);
extern void CopyTileDataTop_0(void *src, u32 offset, u32 size);
extern void TEQSub_Fn35Impl(void *src, u32 offset, u32 size);
extern void CopySomePaletteData(void *src, u32 offset, u32 size);
extern void TEQSub_Fn30Impl(void *src, u32 offset, u32 size);
extern void CopyBgData_Bg3_Bottom(void *src, u32 offset, u32 size);
extern void CopyPaletteBottom(void *src, u32 offset, u32 size);

void Maybe_Keyboard_s_10key(void)
{
    CharData *chr;      /* sp+0: bottom-screen flame char data */
    PaletteData *pal;   /* sp+4: bottom-screen palette */

    /* layout buffers: just remember the file buffer pointers */
    gKeyboardScreen->bnbl_10key = find_buf_fn_from_thumb(data_0216e940);
    gKeyboardScreen->bncl_10key = find_buf_fn_from_thumb(data_0216e958);
    gKeyboardScreen->bnll_10key = find_buf_fn_from_thumb(data_0216e970);
    gKeyboardScreen->bnbl_s = find_buf_fn_from_thumb(data_0216e988);
    gKeyboardScreen->bncl_s = find_buf_fn_from_thumb(data_0216e998);
    gKeyboardScreen->bnll_s = find_buf_fn_from_thumb(data_0216e9a8);

    /* object graphics: parse into the context */
    Gfx_ReadCharGraphics(&gKeyboardScreen->chr, find_buf_fn_from_thumb(data_0216e9b8));
    LoadCellBankFrom(&gKeyboardScreen->cell, find_buf_fn_from_thumb(data_0216e9d0));
    Gfx_ReadPalette(&gKeyboardScreen->pal, find_buf_fn_from_thumb(data_0216e9e8));

    /* upload object chars to top-screen OBJ VRAM (two targets) */
    Arm_FlushRange(gKeyboardScreen->chr->pRawData, gKeyboardScreen->chr->szByte);
    CopyTileDataTop_0(gKeyboardScreen->chr->pRawData, 0, gKeyboardScreen->chr->szByte);
    TEQSub_Fn35Impl(gKeyboardScreen->chr->pRawData, 0, gKeyboardScreen->chr->szByte);

    /* upload object palette: full 0x1a0 at slot 0, plus 0x40 at 0x1c0 */
    Arm_FlushRange(gKeyboardScreen->pal->pRawData, gKeyboardScreen->pal->szByte);
    CopySomePaletteData(gKeyboardScreen->pal->pRawData, 0, 0x1a0);
    CopySomePaletteData((u8 *)gKeyboardScreen->pal->pRawData + 0x1c0, 0x1c0, 0x40);
    TEQSub_Fn30Impl(gKeyboardScreen->pal->pRawData, 0, gKeyboardScreen->pal->szByte);

    /* bottom-screen flame background: chars to BG3 */
    Gfx_ReadCharGraphicsV2(&chr, find_buf_fn_from_thumb(data_0216e9fc));
    Arm_FlushRange(chr->pRawData, chr->szByte);
    CopyBgData_Bg3_Bottom(chr->pRawData, 0, chr->szByte);

    /* two screen maps kept in the context */
    MaybeReadScreenBlock_0(&gKeyboardScreen->scr_flame02, find_buf_fn_from_thumb(data_0216ea14));
    MaybeReadScreenBlock_0(&gKeyboardScreen->scr_flame01, find_buf_fn_from_thumb(data_0216ea30));

    /* bottom-screen BG palette (0x80 bytes) */
    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216ea4c));
    Arm_FlushRange(pal->pRawData, 0x80);
    CopyPaletteBottom(pal->pRawData, 0, 0x80);
}
