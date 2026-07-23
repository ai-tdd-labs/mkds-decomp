// PURPOSE: Sets up the two screen brightness controllers.
// It clears both brightness contexts, enables them, and applies their initial levels.
// The two contexts probably correspond to the DS main and sub display engines.

typedef signed short s16;
typedef unsigned short u16;

typedef struct BrightnessContext {
    u16 unk0;
    u16 enabled;
    u16 unk4;
    u16 unk6;
    s16 brightness;
} BrightnessContext;

extern BrightnessContext data_021755a8;
extern BrightnessContext data_021755b4;
extern void SetBrightness(volatile u16 *registerBase, s16 brightness);

void InitializeBrightnessContexts(void)
{
    // PURPOSE: Sets up the two screen brightness controllers.
    data_021755b4.brightness = 0x10;
    data_021755b4.unk0 = 0;
    data_021755b4.enabled = 1;
    data_021755b4.unk4 = 0;
    data_021755b4.unk6 = 0;

    data_021755a8.unk0 = 0;
    data_021755a8.enabled = 1;
    data_021755a8.unk4 = 0;
    data_021755a8.unk6 = 0;
    data_021755a8.brightness = 0x10;

    SetBrightness((volatile u16 *)0x0400006c, data_021755b4.brightness);
    SetBrightness((volatile u16 *)0x0400106c, data_021755a8.brightness);
}
