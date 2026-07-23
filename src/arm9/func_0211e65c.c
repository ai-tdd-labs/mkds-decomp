/*
 * Advances the shared menu animation counter and writes the paired horizontal
 * interpolation values into both item grids.  The two table sets probably
 * describe the left and right halves of the screen.
 */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    unsigned char _00[4];
    u16 *field_04;
    unsigned char _08[8];
    u16 *field_10;
    unsigned char _14[4];
    u16 *field_18;
    u16 *field_1c;
    unsigned char _20[0x14];
    int field_34;
    unsigned char _38[4];
    int field_3c;
    int field_40;
} AnimationState;

extern AnimationState *gAnimationState;
extern u16 data_0215cf1c[];
extern u16 data_0215cf04[];
extern u16 data_0215cf0c[];
extern u16 ComputeValueInterpolation_from_thumb(int, int, int, int, int);

void func_0211e65c(void)
{
    u16 second;
    u16 selected;
    int i;
    u16 first;
    u16 selected2;

    gAnimationState->field_34++;
    if (*(volatile u16 *)0x027ffc40 == 2) {
        return;
    }

    first = ComputeValueInterpolation_from_thumb(1, 192, 0,
                                                  gAnimationState->field_34, 10);
    second = ComputeValueInterpolation_from_thumb(1, -32, -192,
                                                   gAnimationState->field_34, 10);

    selected = gAnimationState->field_04[3];
    gAnimationState->field_3c = first;
    gAnimationState->field_18[0x283] = first;
    gAnimationState->field_18[0x263] = first;
    gAnimationState->field_18[0x43] = first;
    gAnimationState->field_18[0x23] = first;
    gAnimationState->field_18[3] = first;

    for (i = 0; i < 8; i++) {
        *(u16 *)((unsigned char *)gAnimationState->field_18 +
                 (data_0215cf1c[i] << 6) + 6) = first;
    }
    for (i = 0; i < 4; i++) {
        *(u16 *)((unsigned char *)gAnimationState->field_18 +
                 (data_0215cf04[i] << 6) + 6) = first;
        *(u16 *)((unsigned char *)gAnimationState->field_18 +
                 ((selected + data_0215cf0c[i]) << 6) + 6) = first;
    }

    selected2 = gAnimationState->field_10[3];
    gAnimationState->field_40 = second;
    gAnimationState->field_1c[0x283] = second;
    gAnimationState->field_1c[0x263] = second;
    gAnimationState->field_1c[0x43] = second;
    gAnimationState->field_1c[0x23] = second;
    gAnimationState->field_1c[3] = second;

    for (i = 0; i < 8; i++) {
        *(u16 *)((unsigned char *)gAnimationState->field_1c +
                 (data_0215cf1c[i] << 6) + 6) = second;
    }
    for (i = 0; i < 4; i++) {
        *(u16 *)((unsigned char *)gAnimationState->field_1c +
                 (data_0215cf04[i] << 6) + 6) = second;
        *(u16 *)((unsigned char *)gAnimationState->field_1c +
                 ((selected2 + data_0215cf0c[i]) << 6) + 6) = second;
    }
}
