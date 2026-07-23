// PURPOSE: Updates two fixed-point values from the current configuration.
// The first value is probably derived from a global dimension.
// Both calculations use the same fixed-point divisor.

typedef int fx32;

extern fx32 data_0216cb28;
extern fx32 data_0217d200;
extern fx32 data_0217d208;
extern void FX_Div(void *a0);

void func_02110484(void)
{
    data_0217d200 = ((fx32 (*)(fx32, fx32))FX_Div)((data_0216cb28 - 0x14) << 12, 0x8340000);
    data_0217d208 = ((fx32 (*)(fx32, fx32))FX_Div)(0x61000, 0x8340000);
}
