// PURPOSE: Sets up the multiplayer selection screen graphics and text.
// The first argument supplies the parent heap used to create this screen's heap.
// The other two arguments are saved for later multiplayer menu processing.
// It loads the screen resources, creates two labels, and queues the graphics transfers.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct CharacterData {
    u16 width;
    u16 height;
    u32 pixelFormat;
    u32 mappingType;
    u32 characterFormat;
    u32 size;
    void *data;
} CharacterData;

typedef struct PaletteData {
    u32 format;
    u32 extendedPalette;
    u32 size;
    void *data;
} PaletteData;

typedef struct MultiSelectWork {
    CharacterData *character;
    PaletteData *palette;
    void *cell;
    void *characterFile;
    void *cellFile;
    void *paletteFile;
    void *sprites;
    void *arg1;
    void *arg2;
    void *banner;
    u8 unknown28[0x10];
    int unknown38;
    void *heap;
} MultiSelectWork;

typedef struct SelectRecord {
    s16 index;
    u16 x;
    u16 y;
    s16 unknown06;
    u32 messageId;
} SelectRecord;

extern MultiSelectWork *data_02174e54;
extern char data_0216362c[];
extern char data_02163638[];
extern char data_02163654[];
extern char data_02163670[];
extern char data_0216368c[];
extern char data_021636a4[];
extern char data_021636bc[];
extern SelectRecord data_02153d2c[];

extern void *Mem_CreateOrphanChildHeap(void *heap);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void CARD_func_0054__mkds_3091c(void *destination, unsigned int size);
extern void *find_buf_fn_from_thumb(char *name);
extern int func_02148ca0(void);
extern void Gfx_ReadCharGraphicsRelative(CharacterData **output, void *buffer);
extern void func_020b48b4(void **output, void *buffer);
extern void Gfx_ReadPaletteRelative(PaletteData **output, void *buffer);
extern void func_02124ed0(void *heap, void *characters, void *palette,
                          void **sprites);
extern int func_021243ac(void *heap, int index, void *palette, u16 x, u16 y,
                         int unknown, void *cell, void *characters,
                         void *sprites, int offset);
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, u32 messageId);
extern void func_0212426c(int screen, int index, void *palette, void *message,
                          void *characters, void *sprites);
extern void AllocateReserveTEQSub(int command, int offset, void *source,
                                  int size);
extern void func_02030954(int value);
extern void func_021281c8(int value);
extern void func_0204f804(void);
extern void func_02036820(void *heap);

void Maybe_multi_select_NS_s_nce(void *heap, void *arg1, void *arg2)
{
    int offset;
    int i;
    MultiSelectWork *work;

    heap = Mem_CreateOrphanChildHeap(heap);
    CARD_func_0054__mkds_3091c(
        data_02174e54 = Mem_AllocateHeap(heap, 0x40), 0x40);
    data_02174e54->heap = heap;
    data_02174e54->arg1 = arg1;
    data_02174e54->arg2 = arg2;
    data_02174e54->banner = find_buf_fn_from_thumb(data_0216362c);
    data_02174e54->unknown38 = -0xc0;

    offset = func_02148ca0();
    work = data_02174e54;

    Gfx_ReadCharGraphicsRelative(
        &work->character, find_buf_fn_from_thumb(data_02163638));
    func_020b48b4(&work->cell, find_buf_fn_from_thumb(data_02163654));
    Gfx_ReadPaletteRelative(
        &work->palette, find_buf_fn_from_thumb(data_02163670));
    work->characterFile = find_buf_fn_from_thumb(data_0216368c);
    work->cellFile = find_buf_fn_from_thumb(data_021636a4);
    work->paletteFile = find_buf_fn_from_thumb(data_021636bc);

    func_02124ed0(data_02174e54->heap, work->characterFile,
                  work->paletteFile, &work->sprites);

    for (i = 0; i < 2; i++) {
        int index;
        SelectRecord *record;

        record = &data_02153d2c[i];
        index = data_02153d2c[i].index;
        offset -= func_021243ac(
            data_02174e54->heap, index, work->paletteFile, record->x,
            record->y, record->unknown06, work->cell, work->characterFile,
            work->sprites, offset);
        func_0212426c(
            1, index, work->paletteFile,
            Bmg_GetRawStringPointer_from_thumb(data_02174e54->banner,
                                               record->messageId),
            work->characterFile, work->sprites);
    }

    AllocateReserveTEQSub(0x23, 0, work->character->data,
                          work->character->size);
    AllocateReserveTEQSub(0x1e, 0, work->palette->data,
                          work->palette->size);
    func_02030954(1);
    func_021281c8(0xe);
    func_0204f804();
    func_02036820(data_02174e54->heap);
}
