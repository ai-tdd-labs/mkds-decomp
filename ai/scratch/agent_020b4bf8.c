// PURPOSE: Builds four fixed-point rotation values from an angle and scale.
// The first argument receives the two scaled table values and their mirrored copies.
// A zero scale probably selects the normal fixed-point unit value.

typedef signed int fx32;
typedef signed short s16;

typedef struct RotationValues {
    fx32 scaledSin;
    fx32 scaledCos;
    fx32 negativeCos;
    fx32 copySin;
} RotationValues;

extern s16 data_0215d4b4[];
extern void FX_Div(void *a0);

void func_020b4bf8(RotationValues *values, fx32 scale, int angle)
{
    s16 cosine;
    s16 sine;
    fx32 reciprocal;

    angle >>= 4;
    cosine = data_0215d4b4[angle * 2];
    sine = data_0215d4b4[angle * 2 + 1];
    reciprocal = scale == 0
                     ? 0x1000
                     : ((fx32 (*)(fx32, fx32))FX_Div)(0x1000, scale);
    values->scaledSin = ((long long)sine * reciprocal) >> 12;
    values->scaledCos = ((long long)cosine * reciprocal) >> 12;
    values->negativeCos = -values->scaledCos;
    values->copySin = values->scaledSin;
}
