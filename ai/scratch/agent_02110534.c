// PURPOSE: Divides two shared fixed-point values by the supplied value.
// The function processes the two entries in the shared source array.
// Each quotient is written to the matching slot in the output array.
// The fixed-point divide routine probably returns its result in r0.

typedef int fx32;

extern fx32 data_0215c3a4[];
extern fx32 data_0217d22c[];
extern void FX_Div(void *a0);

void func_02110534(fx32 divisor)
{
    int i;

    for (i = 0; i < 2; i++) {
        data_0217d22c[i] = ((fx32 (*)(fx32, fx32))FX_Div)(data_0215c3a4[i], divisor);
    }
}
