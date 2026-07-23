// PURPOSE: Moves the selected option-menu item and updates the menu state.
// The argument is the requested scroll direction or amount.
// It probably wraps the selection through the available menu entries and starts
// the menu sound when the selection can move.

typedef struct OptionMenuState {
    unsigned char pad_00[0x28];
    int currentValue;
    unsigned char pad_2c[8];
    int soundState;
} OptionMenuState;

typedef struct OptionMenuKindView {
    unsigned char pad_00[0x38];
    int values[6];
    int count;
} OptionMenuKindView;

extern OptionMenuState *data_0217b354;
extern int func_020b2e98(void);
extern int GetCurrentOptionMenuKind_from_thumb(void);
extern void MaybePlaySomeSseqFromSarc0(void *a0);
extern int _s32_div_f(int dividend, int divisor);

#pragma optimize_for_size on

int MaybeOnMenuOptionScroll_from_thumb(int scroll)
{
    int kind;
    int index;
    int count;
    OptionMenuKindView *menu;
    OptionMenuState *volatile state;

    index = 0;
    if (func_020b2e98() != 0) {
        kind = GetCurrentOptionMenuKind_from_thumb();
        menu = (OptionMenuKindView *)((unsigned char *)data_0217b354 + kind * 0x1c);
        count = menu->count;

        while (index < count) {
            if (menu->values[index] == data_0217b354->currentValue)
                break;
            index++;
        }

        if (count == 1) {
            scroll = 0;
        } else if (count == 2) {
            if (scroll != 0 && index + scroll >= 0 && index + scroll < count) {
                data_0217b354->soundState = 0;
                MaybePlaySomeSseqFromSarc0((void *)0);
            } else {
                scroll = 0;
            }
        } else if (scroll != 0) {
            data_0217b354->soundState = 0;
            MaybePlaySomeSseqFromSarc0((void *)0);
        }

        state = data_0217b354;
        state->currentValue = menu->values[_s32_div_f(index + scroll + count, count)];
    }

    return index;
}
