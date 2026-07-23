// PURPOSE: Advances the second state of the choice selection screen.
// This function uses the shared choice context and takes no arguments.
// It probably waits briefly before refreshing the screen graphics.

typedef struct SelectChoisesContext {
    unsigned char unk_00[8];
    int unk_08;
    int unk_0c;
    unsigned char unk_10[0x0c];
    int unk_1c;
    unsigned char unk_20[0x08];
    int unk_28;
} SelectChoisesContext;

extern SelectChoisesContext *data_0217d3f4;
extern void SelectChoisesContext_UpdateGraphics_from_thumb(void);

void SelectChoisesContext_UpdateFn_State2_from_thumb(void)
{
    if (data_0217d3f4->unk_28 != 0) {
        data_0217d3f4->unk_08 = 0;
        data_0217d3f4->unk_28 = 0;
        return;
    }

    data_0217d3f4->unk_0c += 1;
    if (data_0217d3f4->unk_0c >= 15) {
        data_0217d3f4->unk_1c = 1;
        data_0217d3f4->unk_0c = 15;
        return;
    }

    if (data_0217d3f4->unk_0c >= 5) {
        SelectChoisesContext_UpdateGraphics_from_thumb();
    }
}
