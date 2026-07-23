/*
 * STATUS: MATCH (178/178, byte-perfect, 6 reloc-slots wildcarded).
 *
 * func_0211e7c0 — menu/HUD slide-out animation step (thumb).
 * Exact twin of MATCHED func_0211e65c (slide-in): the two ROM bodies are
 * byte-identical modulo literal-pool constants, so this file is the matched
 * twin's source VERBATIM with only the interpolation ranges swapped
 * (0 -> 192 and -192 -> -32 over 10 frames) and the function renamed.
 *
 * LESSON (the wall that cost a previous agent 12+ permutations): the
 * pointer-cursor/struct formulation gets to 172/178 but the final 4-iteration
 * loop colors counter=r4/cursor=r2 instead of the ROM's counter=r2/cursor=r4,
 * and no decl/role permutation fixes it. The reachable coloring comes from a
 * structurally different source: ONE int counter `i` reused by all four loops
 * with INDEXED table access (data_0215cf1c[i], no cursor pointers at all),
 * u16* object fields, and explicit byte-offset address math
 * (*(u16 *)((u8 *)base + (idx << 6) + 6)). mwcc strength-reduces the indexed
 * loads back into cursor increments itself and picks the ROM registers.
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

void func_0211e7c0(void)
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

    first = ComputeValueInterpolation_from_thumb(1, 0, 192,
                                                  gAnimationState->field_34, 10);
    second = ComputeValueInterpolation_from_thumb(1, -192, -32,
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
