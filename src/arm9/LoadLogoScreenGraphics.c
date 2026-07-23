// PURPOSE: Loads the logo screen graphics into video memory.
// The output stores the loaded palette, character graphics, and screen data.
// The screen selector chooses whether the resources go to the top or bottom display.
// The remaining arguments identify the three graphics files to load.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 padding[8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct {
    u8 padding[0x10];
    u32 size;
    void *rawData;
} CharGraphics;

typedef struct {
    u8 padding[8];
    u32 size;
    u8 rawData[1];
} ScreenData;

typedef struct {
    PaletteData *palette;
    CharGraphics *characters;
    ScreenData *screen;
} LogoScreenGraphics;

extern void *find_buf_fn_from_thumb(void *path);
extern void Gfx_ReadPalette(void *output, void *buffer);
extern void Gfx_ReadCharGraphics(void *output, void *buffer);
extern void MaybeReadScreenBlock_0(void *output, void *buffer);
extern void DC_SomeClean(void *address, u32 size);
extern void CopyPaletteTop(void *src, u32 offset, u32 size);
extern void CopyPaletteBottom(void *src, u32 offset, u32 size);
extern void CopyBgData_Bg1_Top(void *src, u32 offset, u32 size);
extern void CopyBgData_Bg1_Bottom(void *src, u32 offset, u32 size);
extern void TEQSub_Fn9Impl(void *src, u32 offset, u32 size);
extern void TEQSub_Fn25Impl(void *src, u32 offset, u32 size);

void LoadLogoScreenGraphics(LogoScreenGraphics *graphics, int topScreen,
                            void *palettePath, void *characterPath,
                            void *screenPath)
{
    Gfx_ReadPalette(&graphics->palette,
                    find_buf_fn_from_thumb(palettePath));
    DC_SomeClean(graphics->palette->rawData, graphics->palette->size);

    if (topScreen != 0) {
        CopyPaletteTop(graphics->palette->rawData, 0,
                       graphics->palette->size);
    } else {
        CopyPaletteBottom(graphics->palette->rawData, 0,
                          graphics->palette->size);
    }

    Gfx_ReadCharGraphics(&graphics->characters,
                         find_buf_fn_from_thumb(characterPath));
    DC_SomeClean(graphics->characters->rawData,
                 graphics->characters->size);

    if (topScreen != 0) {
        CopyBgData_Bg1_Top(graphics->characters->rawData, 0,
                           graphics->characters->size);
    } else {
        CopyBgData_Bg1_Bottom(graphics->characters->rawData, 0,
                              graphics->characters->size);
    }

    MaybeReadScreenBlock_0(&graphics->screen,
                           find_buf_fn_from_thumb(screenPath));
    DC_SomeClean(graphics->screen->rawData, graphics->screen->size);

    if (topScreen != 0) {
        TEQSub_Fn9Impl(graphics->screen->rawData, 0,
                       graphics->screen->size);
    } else {
        TEQSub_Fn25Impl(graphics->screen->rawData, 0,
                        graphics->screen->size);
    }
}
