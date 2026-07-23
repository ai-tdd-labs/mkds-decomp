/* PURPOSE: Initializes the race-rule selection background graphics.
 *
 * Loads character, screen, and palette resources for both screens, queues
 * their video-memory transfers, and adjusts the 32x32 lower-screen tilemap.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 value;
    u8 padding;
} ByteColumn;

typedef struct BackScreen {
    int textSystemContext;
    int selectChoicesContext;
    int selectReturnContext;
    int pageIndex;
    u16 tilemap[1024];
} BackScreen;

extern BackScreen *data_0217d3ec;

extern ByteColumn data_0215d03c[];
extern ByteColumn data_0215d03d[];
extern u8 data_0215d034[];
extern u8 data_0215d030[];
extern u8 data_0215d038[];

extern char *data_0216e390[];
extern char *data_0216e388[];
extern char *data_0216e398[];
extern char *data_0216e380[];
extern char *data_0216e384[];
extern char *data_0216e37c[];

extern char data_0216e484[];
extern char data_0216e4a8[];
extern char data_0216e4d4[];
extern char data_0216e4f8[];

extern void *find_buf_fn_from_thumb(char *name);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void MaybeReadCharBlock_1(void *output, void *buffer);
extern void MaybeReadScreenBlock_0(void *output, void *buffer);
extern void Gfx_ReadPaletteRelative(void *output, void *buffer);
extern void Gfx_ReadCharGraphicsV2(void *output, void *buffer);
extern void Gfx_ReadPalette(void *output, void *buffer);
extern void AllocateReserveTEQSub(int command, int offset, void *source, int size);

int InitializeBackScreen_from_thumb(int graphicsOffset)
{
    int row;
    int subPaletteOffset;
    int subPaletteRemaining;
    int column;
    char *mainCharacters;
    char *mainScreen;
    char *mainPalette;
    char *subCharacters;
    char *subScreen;
    char *subPalette;
    int mainSet;
    int subSet;
    int mainPaletteSlot;
    int subPaletteSlot;
    int mainPaletteOffset;
    int mainPaletteRemaining;

    mainSet = data_0215d03c[data_0217d3ec->pageIndex].value;
    subSet = data_0215d03d[data_0217d3ec->pageIndex].value;
    mainPaletteSlot = data_0215d034[mainSet];
    mainPaletteOffset = mainPaletteSlot << 5;
    mainPaletteRemaining = (0xe - mainPaletteSlot) << 5;
    subPaletteSlot = data_0215d030[subSet];
    subPaletteOffset = subPaletteSlot << 5;
    subPaletteRemaining = (0xc - subPaletteSlot) << 5;

    if (*(volatile u16 *)0x027ffc40 == 2) {
        MaybeReadCharBlock_1(
            &mainCharacters,
            find_buf_fn_from_thumb(data_0216e484));
        MaybeReadScreenBlock_0(
            &mainScreen,
            find_buf_fn_from_thumb(data_0216e4a8));
        Gfx_ReadPaletteRelative(
            &mainPalette,
            find_buf_fn_from_thumb(data_0216e4d4));

        subCharacters = mainCharacters;

        MaybeReadScreenBlock_0(
            &subScreen,
            find_buf_fn_from_thumb(data_0216e4f8));

        subPalette = mainPalette;
    } else {
        if (data_0215d038[mainSet] != 0) {
            Gfx_ReadCharGraphicsV2(
                &mainCharacters,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e390[mainSet]));
            MaybeReadScreenBlock_0(
                &mainScreen,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e388[mainSet]));
            Gfx_ReadPalette(
                &mainPalette,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e398[mainSet]));
        } else {
            Gfx_ReadCharGraphicsV2(
                &mainCharacters,
                find_buf_fn_from_thumb(data_0216e390[mainSet]));
            MaybeReadScreenBlock_0(
                &mainScreen,
                find_buf_fn_from_thumb(data_0216e388[mainSet]));
            Gfx_ReadPalette(
                &mainPalette,
                find_buf_fn_from_thumb(data_0216e398[mainSet]));
        }

        if (data_0215d038[subSet] != 0) {
            Gfx_ReadCharGraphicsV2(
                &subCharacters,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e380[subSet]));
            MaybeReadScreenBlock_0(
                &subScreen,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e384[subSet]));
            Gfx_ReadPalette(
                &subPalette,
                FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
                    data_0216e37c[subSet]));
        } else {
            Gfx_ReadCharGraphicsV2(
                &subCharacters,
                find_buf_fn_from_thumb(data_0216e380[subSet]));
            MaybeReadScreenBlock_0(
                &subScreen,
                find_buf_fn_from_thumb(data_0216e384[subSet]));
            Gfx_ReadPalette(
                &subPalette,
                find_buf_fn_from_thumb(data_0216e37c[subSet]));
        }
    }

    AllocateReserveTEQSub(
        7,
        0,
        *(char **)(mainCharacters + 0x14),
        *(int *)(mainCharacters + 0x10));
    AllocateReserveTEQSub(
        0xb,
        0,
        mainScreen + 0xc,
        *(int *)(mainScreen + 8));
    AllocateReserveTEQSub(
        0xf,
        mainPaletteOffset,
        *(char **)(mainPalette + 0xc) + mainPaletteOffset,
        mainPaletteRemaining);

    graphicsOffset -= *(int *)(subCharacters + 0x10);

    AllocateReserveTEQSub(
        0x15,
        graphicsOffset,
        *(char **)(subCharacters + 0x14),
        *(int *)(subCharacters + 0x10));

    for (row = 0; row < 32; row++) {
        for (column = 0; column < 32; column++) {
            ((BackScreen *)(((u32)(row << 5) << 1)
                            + (int)data_0217d3ec))->tilemap[column] =
                (graphicsOffset >> 5)
                + ((u16 *)((((u32)(row << 5) << 1)
                            + (int)subScreen)
                           + 0xc))[column];
        }
    }

    AllocateReserveTEQSub(
        0x19,
        0,
        (char *)data_0217d3ec + 0x10,
        *(int *)(subScreen + 8));
    AllocateReserveTEQSub(
        0x1f,
        subPaletteOffset,
        *(char **)(subPalette + 0xc) + subPaletteOffset,
        subPaletteRemaining);

    return graphicsOffset;
}
