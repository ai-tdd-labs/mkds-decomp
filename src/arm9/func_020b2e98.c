// PURPOSE: Reports whether either race-options screen is active.
// This function takes no arguments and returns one when a menu or related screen is open.
// The related screen check probably reads a shared menu context pointer.

#pragma optimize_for_size on

typedef struct RaceMenuContext {
    unsigned char pad_00[8];
    void *screen;
} RaceMenuContext;

extern RaceMenuContext *data_0217b354;
extern int IsRaceOptionMenuOn_from_thumb(void);

int func_020b2e98(void)
{
    if (IsRaceOptionMenuOn_from_thumb() != 0 ||
        data_0217b354->screen != 0) {
        return 1;
    }

    return 0;
}
