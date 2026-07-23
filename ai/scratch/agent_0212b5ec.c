/* Sets up the staff-roll (credits) screen state on the bottom/sub engine.
 * Allocates the 0x85c-byte staff-roll context from the given heap and stores
 * it in data_0217d40c, allocates a 0xa0-byte TEQ buffer, configures the sub
 * 2D engine (DISPCNT 0x04001000: BG mode -> 1; BG0CNT 0x04001008: priority 1,
 * char base bits 0x1000), clears BG0 VRAM and fills the screen map with tile 0
 * (palette 15), loads the staff-roll palette ("ending_staffRoll_b_00.nclr")
 * into palette slot 0x1e0, creates a small sprite from tiles, and points the
 * text state at the raw strings of "staffRoll.bmg".
 * Argument: probably the heap to allocate from. */

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* text-draw state embedded at +0x40 of the staff-roll context */
typedef struct {
    void *buf;          /* 0x00: -> tile buffer at ctx+0x20 */
    void *font;         /* 0x04: loaded font 2 */
    int color;          /* 0x08: from ctx->f1c */
    int f4c;            /* 0x0c: cleared */
} TextState;

/* palette block (NNSG2dPaletteData-like): pRawData@0xc */
typedef struct {
    u32 fmt;            /* 0x00 */
    u32 bExtendedPlt;   /* 0x04 */
    u32 szByte;         /* 0x08 */
    void *pRawData;     /* 0x0c */
} PaletteData;

/* staff-roll context, allocated with size 0x85c */
typedef struct {
    int f0;             /* 0x000: cleared */
    int f4;             /* 0x004: cleared */
    int f8;             /* 0x008: cleared (probably frame counter) */
    int fc;             /* 0x00c: 0x70a (probably total duration) */
    int f10;            /* 0x010: cleared */
    int f14;            /* 0x014: -1 (probably current entry index) */
    void *rawString;    /* 0x018: raw string block of staffRoll.bmg */
    s8 f1c;             /* 0x01c: 1 (probably palette/color index) */
    u8 pad1d[3];        /* 0x01d */
    u8 tiles[0x20];     /* 0x020: sprite tile buffer */
    void *textBuf;      /* 0x040: -> tiles */
    void *font;         /* 0x044: loaded font 2 */
    int color;          /* 0x048: from f1c */
    int f4c;            /* 0x04c: cleared */
    u8 charBuf[0x800];  /* 0x050: text char buffer, filled with 0 */
    u8 f850;            /* 0x850: 1 (probably active flag) */
    u8 pad851[3];       /* 0x851 */
    int f854;           /* 0x854: 0x240 */
    void *heap;         /* 0x858: heap the context came from */
} StaffRollData;

extern StaffRollData *data_0217d40c;
extern char data_0216ea78[];    /* "ending_staffRoll_b_00.nclr" */
extern char data_0216ea94[];    /* "staffRoll.bmg" */

extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void InitializeGlobalTEQ(void *buf, int count);
extern void *GetVramBg0BaseOffset_Bottom(void);
extern void Mem_CpuFastMemorySet(u32 value, void *dst, u32 size);
extern void *GetAnotherSubEngineBGOffset(void);
extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadPalette(void *out, void *buf);
extern void AllocateReserveTEQSub(int a, int offset, void *src, int size);
extern void G2d_Sprite_CreateFromTiles(void *tiles, void *dst, int a, int b, int c);
extern void *GetLoadedFont_from_thumb(int index);
extern void Mem_CpuFill8(void *dst, u32 value, u32 size);
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int index);

void LoadStaffRollStuff(void *heap)
{
    PaletteData *pal;       /* sp+0x04 */
    volatile u32 zero;      /* sp+0x08: forces the str/ldr [sp,#8] pair */
    int i;
    TextState *t;
    s8 c;
    void *font;

    data_0217d40c = (StaffRollData *)Mem_AllocateHeap(heap, 0x85c);
    data_0217d40c->heap = heap;
    /* every store goes through the global -> base pointer reloaded each time */
    data_0217d40c->f0 = 0;
    data_0217d40c->f4 = 0;

    InitializeGlobalTEQ(Mem_AllocateHeap(heap, 0xa0), 0xa);

    data_0217d40c->f8 = 0;
    data_0217d40c->f10 = 0;
    data_0217d40c->f14 = -1;
    data_0217d40c->fc = 0x70a;
    data_0217d40c->f1c = 1;
    data_0217d40c->f850 = 1;
    data_0217d40c->f854 = 0x240;

    /* sub engine DISPCNT: BG mode -> 1 */
    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0x1f00) | 0x100;
    /* sub engine BG0CNT: priority -> 1, then keep 0x43 bits and set 0x1000 */
    *(volatile u16 *)0x04001008 = (*(volatile u16 *)0x04001008 & ~3) | 1;
    *(volatile u16 *)0x04001008 = (*(volatile u16 *)0x04001008 & 0x43) | 0x1000;

    /* assignment-as-argument keeps the volatile store after the call */
    Mem_CpuFastMemorySet(zero = 0, GetVramBg0BaseOffset_Bottom(), 0x8000);

    for (i = 0; i < 0x400; i++) {
        /* screen map: tile 0, palette 15 everywhere */
        ((u16 *)GetAnotherSubEngineBGOffset())[i] = i | 0xf000;
    }

    Gfx_ReadPalette(&pal, find_buf_fn_from_thumb(data_0216ea78));
    AllocateReserveTEQSub(0x1f, 0x1e0, (u8 *)pal->pRawData + 0x1e0, 0x20);

    G2d_Sprite_CreateFromTiles(data_0217d40c->tiles, data_0217d40c->charBuf,
                               0x20, 2, 4);

    c = data_0217d40c->f1c;
    font = GetLoadedFont_from_thumb(2);
    /* take the sub-struct pointer BEFORE the first store: the global stays
     * cached in a register for both address computations */
    t = (TextState *)&data_0217d40c->textBuf;
    data_0217d40c->textBuf = data_0217d40c->tiles;
    t->font = font;
    t->color = c;
    t->f4c = 0;
    Mem_CpuFill8(data_0217d40c->charBuf, 0, 0x800);

    data_0217d40c->rawString =
        Bmg_GetRawStringPointer_from_thumb(find_buf_fn_from_thumb(data_0216ea94), 0);
}
