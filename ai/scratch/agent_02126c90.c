// PURPOSE: Advances the first timed state of the text system.
// This function takes no arguments and updates the shared text-system context.
// It probably interpolates two animation values before entering state two.

typedef signed short s16;

typedef struct TextSystemContext {
    unsigned char padding_00[0x04];
    int state;
    unsigned char padding_08[0x04];
    int stateTimer;
    unsigned char padding_10[0x24];
    int field34;
    int field38;
    int tableIndex;
    unsigned char padding_40[0x58];
} TextSystemContext;

extern TextSystemContext *data_0217d3f0;
extern s16 data_0215d040[];

extern int ComputeValueInterpolation_from_thumb(int, int, s16, int, s16);
extern int _s32_div_f(int, int);

void TextSystemContext_UpdateFn_State1_from_thumb(void)
{
    register TextSystemContext **global;
    TextSystemContext *ctx;
    int j;
    int i;

    global = &data_0217d3f0;
    (*global)->stateTimer++;
    for (j = 0, i = 0; j < 2; j++, i += 4) {
        ctx = *global;
        *(int *)((char *)(*global) + 0x54 + i) = ComputeValueInterpolation_from_thumb(
            1,
            data_0215d040[ctx->tableIndex],
            -*(int *)((char *)ctx + 0x5c + i),
            ctx->stateTimer,
            15);
    }

    *(int *)((char *)(*global) + 0x7c) = _s32_div_f((*global)->stateTimer * -10, 15);

    if ((*global)->stateTimer >= 15) {
        if ((*global)->field38 == 0) {
            (*global)->field34 = 0;
        }
        (*global)->state = 2;
        (*global)->stateTimer = 0;
    }
}
