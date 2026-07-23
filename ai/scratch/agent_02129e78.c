// PURPOSE: Queues the selected keyboard flame screen for transfer.
// Uses the current keyboard screen selection to find its background data.

#pragma optimize_for_size on

typedef struct {
    char _00[8];
    int size;
    char data[1];
} ScreenData;

typedef struct {
    char _00[4];
    int screenIndex;
    char _08[0xac];
    ScreenData *screens[2];
} KeyboardScreen;

extern KeyboardScreen *gKeyboardScreen;
extern void AllocateReserveTEQSub(int command, int offset, void *source, int size);

void func_02129e78(void)
{
    ScreenData *screen = gKeyboardScreen->screens[gKeyboardScreen->screenIndex];

    AllocateReserveTEQSub(0x1b, 0, screen->data, screen->size);
}
