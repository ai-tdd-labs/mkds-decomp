// PURPOSE: Prepares the lower-screen graphics and text for this menu.
// It loads the common message file, font, sprite, and background tile data.
// It also copies the finished tile map to the lower-screen background memory.
#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *font;
    u8 sprite[0x20];
    u8 text[0x10];
    u16 tileMap[0x200];
    u8 pad_0434[0x200];
    void *fileBuffer;
    u8 pad_0638[0x14];
    int state;
    void *heap;
} MenuContext;

extern MenuContext *data_02174e6c;
extern char data_021646e0[];

extern void func_02036438(void);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void *GetLoadedFont_from_thumb(int fontType);
extern void *GetVramBg1BaseOffset_Bottom(void);
extern void *Bmg_GetRawStringPointer_from_thumb(void *messageArchive,
                                                int messageId);
extern void G2d_Sprite_CreateFromTiles(void *sprite, void *tiles, int mode,
                                       int option, int extra);
extern void func_020362c4(void *text, void *sprite, void *font, int mode,
                          int option);
extern void func_0203629c(void *text, int x, int y, int color,
                          unsigned int flags, unsigned short *str);
extern void DC_SomeClean(void *ptr, int size);
extern void TEQSub_Fn27Impl_Fn29Impl(void *src, u32 offset, u32 size);
extern void CARD_func_0054__mkds_36264(void *ptr, int size);
extern void TEQSub_Fn25Impl(void *src, u32 offset, u32 size);
extern int func_02035e44(void);
extern void func_02036258(void);
extern void func_02036820(void *heap);

void func_02036108(void)
{
    int column;
    int row;
    void *vram;
    unsigned short *message;

    func_02036438();
    data_02174e6c->state = 9;
    data_02174e6c->fileBuffer =
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_021646e0);
    data_02174e6c->font = GetLoadedFont_from_thumb(0);

    vram = GetVramBg1BaseOffset_Bottom();
    message = Bmg_GetRawStringPointer_from_thumb(data_02174e6c->fileBuffer,
                                                  0x79);
    G2d_Sprite_CreateFromTiles(data_02174e6c->sprite,
                               (u8 *)vram + 0x400, 0x20, 4, 4);
    func_020362c4(data_02174e6c->text, data_02174e6c->sprite,
                  data_02174e6c->font, 1, 4);
    func_0203629c(data_02174e6c->text, 8, 0, 3, 0x209, message);

    for (row = 0x16; row < 0x18; row++) {
        for (column = 0; column < 0x20; column++) {
            data_02174e6c->tileMap[column + (row << 5)] =
                (u16)((((column + row + 1) & 1) << 12) | 1);
        }
    }

    DC_SomeClean(data_02174e6c->tileMap, 0x600);
    TEQSub_Fn27Impl_Fn29Impl(data_02174e6c->tileMap, 0, 0x600);
    CARD_func_0054__mkds_36264(data_02174e6c->tileMap, 0x600);

    for (row = 0x14; row < 0x16; row++) {
        for (column = 0; column < 0x20; column++) {
            data_02174e6c->tileMap[column + (row << 5)] =
                (u16)(column + ((row - 0x14) << 5) + 0x20);
        }
    }

    DC_SomeClean(data_02174e6c->tileMap, 0x600);
    TEQSub_Fn25Impl(data_02174e6c->tileMap, 0, 0x600);
    if (func_02035e44() != 0) {
        func_02036258();
    }
    func_02036820(data_02174e6c->heap);
}
