/* PURPOSE: Loads the graphics and text used by the DS Download Play screen.
 * The heap argument supplies a 0x2c-byte resource holder. The function loads
 * search-icon assets, language-specific font and message data, and the
 * download-screen background assets into that holder.
 */

typedef unsigned int u32;

typedef struct Static2DContents {
    void *searchIconLayout;
    void *searchIconLayoutSecondary;
    void *searchIconCharacters;
    void *searchIconCells;
    void *searchIconPalette;
    u32 messageFont[3];
    void *messageData;
    void *backgroundCharacters;
    void *backgroundPalette;
} Static2DContents;

typedef struct SystemSettings {
    u32 sharedValue;
    int language;
} SystemSettings;

extern Static2DContents *data_0217b4b0;
extern SystemSettings *data_021759d0;

extern char data_0216b09c[];
extern char data_0216b0b0[];
extern char data_0216b0cc[];
extern char data_0216b0e4[];
extern char data_0216b0fc[];
extern char data_0216b114[];
extern char data_0216b124[];
extern char data_0216b134[];
extern char data_0216b144[];
extern char data_0216b154[];
extern char data_0216b164[];
extern char data_0216b174[];
extern char data_0216b184[];
extern char data_0216b194[];
extern char data_0216b1a4[];
extern char data_0216b1b4[];
extern char data_0216b1d0[];

extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void Gfx_ReadCharGraphics(void *destination, void *buffer);
extern void LoadCellBankFrom(void *destination, void *buffer);
extern void Gfx_ReadPalette(void *destination, void *buffer);
extern void NFTR_Load(void *font, void *buffer);
extern void Gfx_ReadCharGraphicsV2(void *destination, void *buffer);

void LoadStatic2DContents(void *heap)
{
    data_0217b4b0 = Mem_AllocateHeap(heap, 0x2c);

    data_0217b4b0->searchIconLayout =
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b09c);
    data_0217b4b0->searchIconLayoutSecondary =
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b0b0);
    Gfx_ReadCharGraphics(
        &data_0217b4b0->searchIconCharacters,
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b0cc));
    LoadCellBankFrom(
        &data_0217b4b0->searchIconCells,
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b0e4));
    Gfx_ReadPalette(
        &data_0217b4b0->searchIconPalette,
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b0fc));

    switch (data_021759d0->language) {
    case 0:
    case 1:
    default:
        NFTR_Load(
            data_0217b4b0->messageFont,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b114));
        break;
    case 2:
        NFTR_Load(
            data_0217b4b0->messageFont,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b124));
        break;
    case 3:
        NFTR_Load(
            data_0217b4b0->messageFont,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b134));
        break;
    case 4:
        NFTR_Load(
            data_0217b4b0->messageFont,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b144));
        break;
    case 5:
        NFTR_Load(
            data_0217b4b0->messageFont,
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b154));
        break;
    }

    switch (data_021759d0->language) {
    case 0:
    case 1:
    default:
        data_0217b4b0->messageData =
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b164);
        break;
    case 2:
        data_0217b4b0->messageData =
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b174);
        break;
    case 3:
        data_0217b4b0->messageData =
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b184);
        break;
    case 4:
        data_0217b4b0->messageData =
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b194);
        break;
    case 5:
        data_0217b4b0->messageData =
            FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b1a4);
        break;
    }

    Gfx_ReadCharGraphicsV2(
        &data_0217b4b0->backgroundCharacters,
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b1b4));
    Gfx_ReadPalette(
        &data_0217b4b0->backgroundPalette,
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216b1d0));
}
