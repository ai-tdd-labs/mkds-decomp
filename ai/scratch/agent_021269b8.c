// PURPOSE: Advances the third state of the text system.
// This function takes no arguments.
// It probably delays the next text state while refreshing button graphics.

typedef struct TextSystemContext {
    unsigned char padding_00[0x4];
    int state;                         /* +0x4 */
    unsigned char padding_08[0x4];
    int stateTimer;                    /* +0xc */
    unsigned char padding_10[0x20];
    int completionFlag;                /* +0x30 */
    unsigned char padding_34[0x2218];
    int buttonGraphicsState;           /* +0x224c */
} TextSystemContext;

extern TextSystemContext *data_0217d3f0;
extern void TextSystemContext_ReloadButtonGraphics_from_thumb(void);

void TextSystemContext_UpdateFn_State3_from_thumb(void)
{
    data_0217d3f0->stateTimer++;
    data_0217d3f0->buttonGraphicsState = 0;

    if (data_0217d3f0->stateTimer >= 10) {
        data_0217d3f0->completionFlag = 1;
        data_0217d3f0->state = 2;
        data_0217d3f0->stateTimer = 0;
    } else if (data_0217d3f0->stateTimer >= 5) {
        TextSystemContext_ReloadButtonGraphics_from_thumb();
    }
}
