/*
 * func_0211e65c — probably a menu/HUD slide-in animation step (thumb).
 * Increments a frame counter in the global state, returns early when the
 * shared-WRAM state halfword (0x027ffc40) == 2, then interpolates two
 * offset values (0xc0->0 and -0x20->-0xc0 over 10 frames) and writes them
 * into the u16 field at +6 of many 0x40-stride entries of two arrays
 * (offsets 0x18 and 0x1c), picking entries directly (20,19,2,1,0) and via
 * u16 index tables (data_0215cf1c / data_0215cf04 / data_0215cf0c).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

/* 0x40-stride entry, u16 value at offset 6 (probably an OAM/sprite cell) */
typedef struct UnkEntry {
    u8 pad0[6];
    s16 h6;               /* +0x06: the animated value (can go negative) */
    u8 pad8[0x38];
} UnkEntry;

/* header object with an entry count at +6 */
typedef struct UnkHeader {
    u8 pad0[6];
    u16 count6;           /* +0x06 */
} UnkHeader;

typedef struct UnkState {
    u8 pad00[4];          /* +0x00 */
    UnkHeader *hdr04;     /* +0x04 */
    u8 pad08[8];          /* +0x08 */
    UnkHeader *hdr10;     /* +0x10 */
    u8 pad14[4];          /* +0x14 */
    UnkEntry *arr18;      /* +0x18 */
    UnkEntry *arr1c;      /* +0x1c */
    u8 pad20[0x14];       /* +0x20 */
    int counter34;        /* +0x34: frame counter */
    u8 pad38[4];          /* +0x38 */
    int val3c;            /* +0x3c: interpolated value 1 */
    int val40;            /* +0x40: interpolated value 2 */
} UnkState;

extern UnkState *gAnimationState;

extern u16 data_0215cf1c[8];  /* index table, 8 entries */
extern u16 data_0215cf04[4];  /* index table, 4 entries */
extern u16 data_0215cf0c[4];  /* index table, 4 entries (offset by count) */

/* returns a 16-bit value: stored via strh with no truncation in the caller */
extern s16 ComputeValueInterpolation_from_thumb(int type, int from, int to, int t, int dur);

void func_0211e65c(void)
{
    s16 v2;
    s16 v1;
    int cnt;
    int i;
    int j;
    const u16 *pa;
    const u16 *pb;

    gAnimationState->counter34++;
    if (*(volatile u16 *)0x027ffc40 == 2) {
        return;
    }
    v1 = ComputeValueInterpolation_from_thumb(1, 0xc0, 0, gAnimationState->counter34, 10);
    v2 = ComputeValueInterpolation_from_thumb(1, -0x20, -0xc0, gAnimationState->counter34, 10);

    /* first array (+0x18): value v1 */
    cnt = gAnimationState->hdr04->count6;
    gAnimationState->val3c = v1;
    gAnimationState->arr18[20].h6 = v1;
    gAnimationState->arr18[19].h6 = v1;
    gAnimationState->arr18[2].h6 = v1;
    gAnimationState->arr18[1].h6 = v1;
    gAnimationState->arr18[0].h6 = v1;
    for (i = 0, pa = data_0215cf1c; i < 8; i++) {
        gAnimationState->arr18[*pa].h6 = v1;
        pa++;
    }
    for (j = 0, pa = data_0215cf04, pb = data_0215cf0c; j < 4; j++) {
        gAnimationState->arr18[*pa].h6 = v1;
        gAnimationState->arr18[cnt + *pb].h6 = v1;
        pa++;
        pb++;
    }

    /* second array (+0x1c): value v2 */
    cnt = gAnimationState->hdr10->count6;
    gAnimationState->val40 = v2;
    gAnimationState->arr1c[20].h6 = v2;
    gAnimationState->arr1c[19].h6 = v2;
    gAnimationState->arr1c[2].h6 = v2;
    gAnimationState->arr1c[1].h6 = v2;
    gAnimationState->arr1c[0].h6 = v2;
    for (i = 0, pa = data_0215cf1c; i < 8; i++) {
        gAnimationState->arr1c[*pa].h6 = v2;
        pa++;
    }
    for (j = 0, pa = data_0215cf04, pb = data_0215cf0c; j < 4; j++) {
        gAnimationState->arr1c[*pa].h6 = v2;
        gAnimationState->arr1c[cnt + *pb].h6 = v2;
        pa++;
        pb++;
    }
}
