// PURPOSE: Initializes three shared fixed-point ratios.
//
// Divides one fixed-point unit by each of three configured values and stores
// the results in their corresponding shared output slots. The values likely
// configure related display or scene scaling ratios.

typedef int fx32;

extern void FX_Div(void *a0);

extern fx32 data_02161ae4;
extern fx32 data_02161ae0;
extern fx32 data_02161adc;
extern fx32 data_02174e10;
extern fx32 data_02174e0c;
extern fx32 data_02174e08;

void func_020250a8(void)
{
    data_02174e10 = ((fx32 (*)(fx32, fx32))FX_Div)(0x1000, data_02161ae4);
    data_02174e0c = ((fx32 (*)(fx32, fx32))FX_Div)(0x1000, data_02161ae0);
    data_02174e08 = ((fx32 (*)(fx32, fx32))FX_Div)(0x1000, data_02161adc);
}
