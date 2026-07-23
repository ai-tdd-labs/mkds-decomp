/* PURPOSE: Sets up race-start speed constants and, for one special course, tells a
 * just-loaded kart model to fade some of its materials in.
 *
 * Writes a couple of fixed-point constants into globals (probably related to
 * an initial speed/acceleration setup at race start), computes a squared
 * speed-like value from a 64-bit fixed-point multiply of data_0217bd3c and a
 * field at data_0217bc34+0x3b4, then loads the "koura_w" (Rainbow Road?)
 * kart model/texture pair. If the current race's courseName index is 0x1d
 * (29), it marks the loaded model's nested model block somehow-translucent
 * via Maybe_helper_013044.
 */

typedef int fx32;
typedef long long fx64;

typedef struct ModelBlock {
    unsigned char pad_00[0x18];
    unsigned char numMaterials;
} ModelBlock;

/* Wrapper object returned by func_020ed490; its +4 field is the nested
 * ModelBlock pointer used below (probably a "kart entry" style struct). */
typedef struct StructML {
    unsigned char pad0[4];
    ModelBlock *model; /* +4 */
} StructML;

/* Probably the current race/scene configuration (same layout used by
 * Arc_MountArchive_from_thumb.c). courseName is a union of char* / int. */
typedef struct RaceConfig {
    char *courseName; /* +0x0 */
    int f4;
    int raceMode; /* +0x8 */
    int sceneId;  /* +0xc */
} RaceConfig;

extern int data_0217bd3c;
extern int data_0217bd40;
extern int data_0217bd44;
extern int *data_0217bc34;
extern int data_0217bd34;
extern StructML *data_0217bd38;
extern char data_0216c6f4[]; /* "koura_w.nsbmd" */
extern char data_0216c704[]; /* "koura_w.nsbtx" */
extern RaceConfig *gRaceConfig;

extern fx32 FX_Div(fx32 num, fx32 den);
extern fx64 Multiply64(fx64 a, fx64 b);
extern StructML *func_020ed490(char *nsbmd, char *nsbtx);
extern void Maybe_helper_013044(ModelBlock *model, int arg1);

void func_020fad00(void)
{
    fx64 a, b, prod;
    StructML *ml;

    data_0217bd3c = 0x1e000;
    data_0217bd40 = FX_Div(0x1000, 0x1e000);

    data_0217bd44 = 0x299a;

    a = (fx64)data_0217bd3c;
    b = (fx64) * (int *)((char *)data_0217bc34 + 0x3b4);
    prod = Multiply64(a, b);
    data_0217bd34 = (int)(prod >> 12);
    data_0217bd34 = data_0217bd34 >> 12;
    data_0217bd34 = data_0217bd34 * data_0217bd34;

    ml = func_020ed490(data_0216c6f4, data_0216c704);
    data_0217bd38 = ml;
    if ((int)gRaceConfig->courseName == 0x1d) {
        Maybe_helper_013044(ml->model, 0);
    }
}
