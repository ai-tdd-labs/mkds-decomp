// PURPOSE: Shows a multiplayer error message on the top screen.
// This function takes no arguments. It chooses the active font, prints the
// prepared error text, builds the background tilemap, and uploads both tile
// buffers. The exact visual meaning of the tile values is probably UI-specific.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *sprite;
    void *font;
    u32 field_08;
    u32 field_0c;
} MultiplayErrorText;

typedef struct {
    u32 errorKind;
    u32 errorArgument;
    u16 *errorString;
    u32 hasError;
    u32 field_10;
    u8 backgroundSprite[0x20];
    MultiplayErrorText text;
    u32 backgroundTiles[0x500];
    u16 temporaryTilemap[0x300];
} MultiplayErrorWork;

extern MultiplayErrorWork *data_0217d408;

extern void Clear1A44SomeTileData_from_thumb(void);
extern void *GetGlobal2DObject(void);
extern void *GetLoadedFont_from_thumb(int index);
extern void G2d_Text_PrintString(void *text, int x, int y, int color,
                                 u32 flags, u16 *string);
extern void CleanTemporaryMultiplayErrorBuffer_from_thumb(void);
extern void Arm_FlushRange(void *address, u32 size);
extern void CopyBgData_Bg1_Top(void *src, u32 offset, u32 size);
extern void TEQSub_Fn9Impl(void *src, u32 offset, u32 size);

void DrawMultiplayError_from_thumb(void)
{
    int i;

    Clear1A44SomeTileData_from_thumb();

    if (*(volatile u16 *)0x027ffc40 == 2) {
        data_0217d408->text.font = (u8 *)GetGlobal2DObject() + 0x14;
    } else {
        data_0217d408->text.font = GetLoadedFont_from_thumb(0);
    }

    G2d_Text_PrintString(&data_0217d408->text, 0x80, 0x14, 0xe,
                         0x412, data_0217d408->errorString);
    CleanTemporaryMultiplayErrorBuffer_from_thumb();

    for (i = 0; i < 0x300; i++) {
        if (i >= 0x120 && i < 0x1c0) {
            data_0217d408->temporaryTilemap[i] =
                (i - 0x120) | 0xf000;
        } else {
            data_0217d408->temporaryTilemap[i] = 0xf09f;
        }
    }

    *(volatile u16 *)0x050001fc = 0xffff;
    *(volatile u16 *)0x05000000 = 0;
    *(volatile u32 *)0x04000014 = 0;

    *(volatile u16 *)0x0400000a &= ~3;
    *(volatile u16 *)0x0400000a &= ~0x40;
    *(volatile u16 *)0x0400000a =
        (*(volatile u16 *)0x0400000a & 0x43) | 0x400;

    Arm_FlushRange(data_0217d408->backgroundTiles, 0x1400);
    Arm_FlushRange(data_0217d408->temporaryTilemap, 0x600);
    CopyBgData_Bg1_Top(data_0217d408->backgroundTiles, 0, 0x1400);
    TEQSub_Fn9Impl(data_0217d408->temporaryTilemap, 0, 0x600);
}
