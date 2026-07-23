// PURPOSE: Clears the saved black brightness state for both screens.

typedef signed short s16;
typedef unsigned short u16;

typedef struct BrightnessState {
    u16 mode;
    u16 value0;
    u16 value1;
    u16 value2;
    s16 brightness;
} BrightnessState;

extern BrightnessState data_021755b4;
extern BrightnessState data_021755a8;
extern void SetBrightness(volatile u16 *registerAddress, s16 brightness);

void Bright_ResetBlackBothScreens(void)
{
    const u16 two = 2;
    const u16 zero = 0;

    data_021755b4.brightness = zero;
    data_021755b4.mode = two;
    data_021755b4.value0 = zero;
    data_021755b4.value1 = zero;
    data_021755b4.value2 = zero;
    data_021755a8.mode = two;
    data_021755a8.value0 = zero;
    data_021755a8.value1 = zero;
    data_021755a8.value2 = zero;
    data_021755a8.brightness = zero;
    SetBrightness((volatile u16 *)0x0400006c, data_021755b4.brightness);
    SetBrightness((volatile u16 *)0x0400106c, data_021755a8.brightness);
}
