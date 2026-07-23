// PURPOSE: Assigns race-state columns to the active racers.
// The function checks four racer slots and marks unavailable slots with -1.
// Active slots receive consecutive column numbers and are copied by the helper.
// The exact purpose of the four-byte race-state fields is probably column mapping.

typedef unsigned char u8;
typedef unsigned int u32;

extern u8 *data_0217d384;
extern void func_0205d0e8(int dst_column, int src_column);

void func_02122684(void)
{
    signed char column;
    u8 racer;

    column = 0;
    racer = column;
    for (; (u32)racer < 4; racer++) {
        if ((u32)racer >= data_0217d384[0x1f53]) {
            data_0217d384[0x1f4e + racer] = -1;
        } else if (!(data_0217d384[0x1f55] & (1 << racer))) {
            data_0217d384[0x1f4e + racer] = -1;
        } else {
            int old_column;

            old_column = data_0217d384[0x1f4e + racer];
            data_0217d384[0x1f4e + racer] = column;
            column++;
            func_0205d0e8(old_column, data_0217d384[0x1f4e + racer]);
        }
    }
}
