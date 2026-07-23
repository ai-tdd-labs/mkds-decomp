/* Loads the graphics of the "select choises" screen (bottom screen):
 * char data (.ncgr) is placed at the end of the supplied VRAM offset
 * (offset -= szByte), the 32x32 screenmap (.nscr) is copied into the
 * context (+0x2c) with the tile base (offset>>5) added per entry, and the
 * palette (.nclr) is copied from +0x1c0 into palette slot 0x1c0 (0x40 bytes).
 * Probably f_82c/f_830 are tile indices for two cursor/choice sprites,
 * computed from position bytes in data_0215d0a0. Returns the new offset. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char data_0216e840[]; /* "select_choises_s_b.ncgr" */
extern char data_0216e858[]; /* "select_choises_s_bg.nscr" */
extern char data_0216e874[]; /* "select_choises_s_b.nclr" */

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

/* screenmap block (NNSG2dScreenData-like): szByte@0x8, rawData@0xc */
typedef struct {
    u16 screenWidth;    /* 0x00 */
    u16 screenHeight;   /* 0x02 */
    u16 colorMode;      /* 0x04 */
    u16 screenFormat;   /* 0x06 */
    u32 szByte;         /* 0x08 */
    u16 rawData[1];     /* 0x0c */
} ScreenData;

/* palette block (NNSG2dPaletteData-like): pRawData@0xc */
typedef struct {
    u32 fmt;            /* 0x00 */
    u32 bExtendedPlt;   /* 0x04 */
    u32 szByte;         /* 0x08 */
    void *pRawData;     /* 0x0c */
} PaletteData;

/* context of the select-choises screen */
typedef struct {
    u8 pad0[0x2c];      /* 0x000 */
    u16 map[0x400];     /* 0x02c: 32x32 screenmap copy */
    u32 f_82c;          /* 0x82c: probably tile index of sprite A */
    u32 f_830;          /* 0x830: probably tile index of sprite B */
    u8 pad834[0x68];    /* 0x834 */
    u32 charBase;       /* 0x89c: tile base of the loaded chars */
} SelectChoisesContext;

extern SelectChoisesContext *data_0217d3f4;
extern u8 data_0215d0a0[]; /* position bytes: [0]=x tile, [2]=y tile */

extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void MaybeReadCharBlock_1(CharData **out, void *buf);
extern void MaybeReadScreenBlock(ScreenData **out, void *buf);
extern void Gfx_ReadPaletteRelative(PaletteData **out, void *buf);
extern void Arm_FlushRange(void *ptr, u32 size);
extern void CopyBgData_Bg0_Bottom(void *src, u32 offset, u32 size);
extern void TEQSub_Fn24Impl(void *src, u32 offset, u32 size);
extern void CopyPaletteBottom(void *src, u32 offset, u32 size);

int SelectChoisesContext_LoadGraphics_from_thumb(int offset)
{
    int i;              /* sp+0x04 */
    int j;              /* sp+0x08 */
    CharData *chr;      /* sp+0x0c */
    ScreenData *scr;    /* sp+0x10 */
    PaletteData *pal;   /* sp+0x14 */
    int base;
    int row;            /* running row index (i*0x20) */

    MaybeReadCharBlock_1(&chr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e840));
    MaybeReadScreenBlock(&scr, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e858));
    Gfx_ReadPaletteRelative(&pal, FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216e874));

    offset -= chr->szByte;
    base = offset >> 5; /* 32 bytes per 4bpp tile */
    data_0217d3f4->charBase = base;

    Arm_FlushRange(chr->pRawData, chr->szByte);
    CopyBgData_Bg0_Bottom(chr->pRawData, offset, chr->szByte);

    for (i = 0, row = 0; i < 0x20; i++) {
        for (j = 0; j < 0x20; j++) {
            /* byte offsets made explicit: (row<<1) shared per row, j*2 as
             * its own induction variable — needed for exact codegen */
            *(u16 *)(j * 2 + (((u32)row << 1) + (u32)data_0217d3f4->map)) =
                base + *(u16 *)((((u32)row << 1) + (u32)scr->rawData) + j * 2);
        }
        row += 0x20;
    }

    Arm_FlushRange(data_0217d3f4->map, scr->szByte);
    TEQSub_Fn24Impl(data_0217d3f4->map, 0, scr->szByte);

    data_0217d3f4->f_82c = data_0217d3f4->charBase + (data_0215d0a0[0] + (data_0215d0a0[2] << 5));
    data_0217d3f4->f_830 = data_0217d3f4->charBase + ((data_0215d0a0[2] << 5) + (data_0215d0a0[0] + 3));

    Arm_FlushRange(pal->pRawData, 0x1c0);
    CopyPaletteBottom((u8 *)pal->pRawData + 0x1c0, 0x1c0, 0x40);

    return offset;
}
