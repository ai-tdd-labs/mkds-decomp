// PURPOSE: Queues the choice screen graphics tiles for transfer.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SelectChoisesContext {
    u8 unk_000[0x08];
    int unk_008;
    int unk_00c;
    u8 unk_010[0x10];
    int unk_020;
    int unk_024;
    u8 unk_028[0x86c];
    void *unk_894[2];
    int unk_89c;
    int unk_8a0;
} SelectChoisesContext;

extern SelectChoisesContext *data_0217d3f4;

extern void SelectChoisesContext_UpdateGraphics_from_thumb(void);
extern void AllocateReserveTEQSub(int command, int offset, void *source, int size);

void SelectChoisesContext_UpdateFn_State0_from_thumb(void)
{
    int i;
    int tile_row;
    int source_offset;
    int j;
    int tile_offset;

    if (data_0217d3f4->unk_8a0 != 0) {
        SelectChoisesContext_UpdateGraphics_from_thumb();
        data_0217d3f4->unk_008 = 1;
        i = 0;
        data_0217d3f4->unk_024 = i;
        data_0217d3f4->unk_00c = i;
        data_0217d3f4->unk_020 = i;

        if (data_0217d3f4->unk_8a0 != 0) {
            for (tile_row = i, source_offset = i; i < 2;
                 tile_row += 2, source_offset += 4, i += 1) {
                for (j = 0, tile_offset = 5; j < 2;
                     tile_offset += 0x20, j += 1) {
                    if (*(volatile u16 *)0x027ffc40 != 2) {
                        AllocateReserveTEQSub(
                            0x14,
                            (data_0217d3f4->unk_89c + (((j + tile_row) << 5) + 5)) << 5,
                            (u8 *)*(void **)((u8 *)data_0217d3f4 + source_offset + 0x894)
                                + (tile_offset << 5),
                            0x360);
                    }
                }
            }
        }
    }
}
