// PURPOSE: Plays a sound based on the current menu selection.
//
// Reads the current selection from the active menu state.
// The two sound choices probably correspond to related menu actions.

typedef struct MenuState {
    char _00[0x54];
    int selection;
} MenuState;

extern MenuState *data_0217b340;
extern void MaybePlaySomeSseqFromSarc0(int sequence);

#pragma optimize_for_size on
void func_020acf04(void)
{
    switch (data_0217b340->selection) {
    case 0:
    case 1:
    case 2:
        MaybePlaySomeSseqFromSarc0(9);
        break;
    case 3:
    case 4:
        MaybePlaySomeSseqFromSarc0(8);
        break;
    }
}
