// PURPOSE: Loads menu graphics and queues their character and palette data.

typedef struct ResourceBlock {
    void *unknown0;
    void *unknown4;
    int size8;
    void *dataC;
    int size10;
    void *data14;
} ResourceBlock;

extern void *find_buf_fn_from_thumb(char *path);
extern void func_020b48b4(void **payload, void *container);
extern void Gfx_ReadCharGraphicsRelative(void **graphics, void *file);
extern void Gfx_ReadPaletteRelative(void **output, void *buffer);
extern void AllocateReserveTEQSub(int command, int offset, void *source,
                                  int size);

extern char *data_0216e124;
extern char *data_0216e128;
extern char *data_0216e12c;
extern char *data_0216e130;
extern char *data_0216e134;
extern void **data_0217d380;

void func_0211f61c(void)
{
    ResourceBlock *character = 0;
    ResourceBlock *palette = 0;

    func_020b48b4(data_0217d380,
                  find_buf_fn_from_thumb(data_0216e128));
    Gfx_ReadCharGraphicsRelative(&character,
                                 find_buf_fn_from_thumb(data_0216e134));
    Gfx_ReadPaletteRelative(&palette,
                            find_buf_fn_from_thumb(data_0216e130));
    data_0217d380[1] = find_buf_fn_from_thumb(data_0216e124);
    data_0217d380[3] = find_buf_fn_from_thumb(data_0216e12c);
    AllocateReserveTEQSub(0x23, 0, character->data14, character->size10);
    AllocateReserveTEQSub(0x1e, 0, palette->dataC, palette->size8);
}
