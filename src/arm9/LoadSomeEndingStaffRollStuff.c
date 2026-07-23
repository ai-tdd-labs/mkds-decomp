// PURPOSE: Loads graphics for the ending staff roll.
// It allocates the ending-roll object data and initializes its OAM records.
// It probably loads the palette, character graphics, and cell data for the credits.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 format;
    u32 extended_palette;
    u32 size;
    void *raw_data;
} PaletteData;

typedef struct {
    u16 width;
    u16 height;
    u32 pixel_format;
    u32 mapping_type;
    u32 character_format;
    u32 size;
    void *raw_data;
} CharacterData;

typedef struct {
    u32 reserved_low : 10;
    u32 priority : 2;
    u32 reserved_high : 20;
    u32 second_word;
} EndingOamRecord;

typedef struct {
    int frame_count;
    PaletteData *palette;
    CharacterData *characters;
    void *first_cell;
    EndingOamRecord oam[128];
    u32 unused_tail;
} EndingStaffRollObjectData;

extern EndingStaffRollObjectData *data_0217b4ac;
extern char data_0216b03c[];
extern char data_0216b05c[];
extern char data_0216b07c[];

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *func_020b47c0(char *name);
extern void Gfx_ReadPalette(void *destination, void *buffer);
extern void Gfx_ReadCharGraphics(void *destination, void *buffer);
extern void LoadCellBankFrom(void *destination, void *buffer);
extern void *CellBank_GetMetatileEntry(void *cell_bank, u16 index);
extern void CopySomePaletteData(void *source, u32 offset, u32 size);
extern void CopyTileDataTop_0(void *source, u32 offset, u32 size);

void LoadSomeEndingStaffRollStuff(void)
{
    void *cell_bank;
    int i;

    data_0217b4ac = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x414);

    for (i = 0; i < 128; i++) {
        data_0217b4ac->oam[i].priority = 3;
    }

    data_0217b4ac->frame_count = 0;
    Gfx_ReadPalette(&data_0217b4ac->palette, func_020b47c0(data_0216b03c));
    Gfx_ReadCharGraphics(&data_0217b4ac->characters, func_020b47c0(data_0216b05c));
    LoadCellBankFrom((cell_bank = 0, &cell_bank),
                     func_020b47c0(data_0216b07c));
    data_0217b4ac->first_cell = CellBank_GetMetatileEntry(cell_bank, 0);

    CopySomePaletteData(data_0217b4ac->palette->raw_data, 0,
                        data_0217b4ac->palette->size);
    CopyTileDataTop_0(data_0217b4ac->characters->raw_data, 0,
                      data_0217b4ac->characters->size);

    *(volatile u32 *)0x04000000 =
        (*(volatile u32 *)0x04000000 & 0xffcfffef) | 0x10;
}
