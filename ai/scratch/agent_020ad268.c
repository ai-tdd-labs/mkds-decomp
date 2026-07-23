// PURPOSE: Configures the title screen fade effect.
// Advances the title menu fade timer and applies the matching alpha blend.
// The final phase probably skips the title intro and marks the menu ready.

typedef signed short s16;

typedef struct TitleState {
    unsigned char _00[0x50];
    int menuReady;
    unsigned char _54[0x10];
    int fadeTimer;
} TitleState;

extern TitleState *data_0217b340;
extern void EnableAlphaSetTopBldcntBldalpha(s16 firstTargetPixels,
                                             s16 secondTargetPixels,
                                             s16 evaCoefficient,
                                             s16 evbCoefficient);
extern void SetB488TitleMenuSkipIntro(int enabled);

void Title_SomeBldalphaConfig_from_thumb(void)
{
    int timer;

    timer = data_0217b340->fadeTimer++;
    if (timer < 0x1e) {
        EnableAlphaSetTopBldcntBldalpha(4, 8, 0, 0x10);
    } else if (timer < 0x2f) {
        timer -= 0x1e;
        EnableAlphaSetTopBldcntBldalpha(4, 8, timer, 0x10 - timer);
    } else if (timer < 0x6b) {
        EnableAlphaSetTopBldcntBldalpha(0, 0, 0, 0);
    } else {
        EnableAlphaSetTopBldcntBldalpha(0, 0, 0, 0);
        SetB488TitleMenuSkipIntro(1);
        data_0217b340->menuReady = 1;
        data_0217b340->fadeTimer--;
    }
}
