// PURPOSE: Prepares and transfers the graphics resources needed by a screen.
// The first argument selects one of two graphics memory areas.
// The second argument is probably a heap used to prepare sprite data.
// The third argument provides the character, palette, and screen resource blocks.

typedef struct ResourceBlock {
    void *unknown0;
    void *unknown4;
    int size8;
    char *dataC;
    int size10;
    void *data14;
} ResourceBlock;

typedef struct ScreenResources {
    ResourceBlock *screen;
    ResourceBlock *graphics;
    int unknown8;
    void *characters;
    void *unknown10;
    void *palette;
    void *spriteData;
} ScreenResources;

extern void func_02124ed0(void *heap, void *characters, void *palette,
                          void **spriteData);
extern void AllocateReserveTEQSub(int command, int offset, void *source,
                                  int size);

void func_02025a50(int alternate, void *heap, ScreenResources *resources)
{
    int command;

    func_02124ed0(heap, resources->characters, resources->palette,
                  &resources->spriteData);

    if (alternate == 0) {
        command = 0x13;
        AllocateReserveTEQSub(0x0e, 0, resources->graphics->dataC, 0x1a0);
        AllocateReserveTEQSub(0x0e, 0x1c0,
                              resources->graphics->dataC + 0x1c0, 0x40);
    } else {
        command = 0x23;
        AllocateReserveTEQSub(0x1e, 0, resources->graphics->dataC,
                              resources->graphics->size8);
    }

    AllocateReserveTEQSub(command, 0, resources->screen->data14,
                          resources->screen->size10);
}
