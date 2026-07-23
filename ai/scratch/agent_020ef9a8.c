// PURPOSE: Updates an object's two scaled position vectors.

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad00[0x50];
    VecFx32 f50;
} Target;

typedef struct {
    char pad00[0x14];
    Target *f14;
    char pad18[0x38 - 0x18];
    VecFx32 f38;
    VecFx32 f44;
    VecFx32 f50;
    char pad5c[0x78 - 0x5c];
    int f78;
    char pad7c[0x8c - 0x7c];
    int f8c;
    VecFx32 f90;
    VecFx32 f9c;
    VecFx32 fa8;
    char padb4[0xe8 - 0xb4];
    int fe8;
} State;

extern void VecFx32_AddScale1(int scale, VecFx32 *dir, VecFx32 *base,
                               VecFx32 *out);

void func_020ef9a8(State *state)
{
    state->f90 = state->f44;
    state->f9c.x = -state->f44.x;
    state->f9c.y = -state->f44.y;
    state->f9c.z = -state->f44.z;

    VecFx32_AddScale1(
        state->f78 + (int)(((long long)state->f8c << 14) >> 12),
        &state->f9c, &state->f50, &state->fa8);
    VecFx32_AddScale1((int)(((long long)state->fe8 * state->f8c) >> 12),
                       &state->f38, &state->fa8, &state->f14->f50);
}
