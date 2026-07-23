// PURPOSE: Scales a racer value by the course state's stored factor.
// The racer ID selects the value to scale.
// The factor is probably a fixed-point course setting at offset 0x108.
// The result uses 12 fractional bits with rounding.

extern int *data_02175620;
extern int GetSomeRacerValue(int racerId);

int func_020853a4(int racerId) {
    int factor = data_02175620[0x42];
    int value = GetSomeRacerValue(racerId);
    return (int)(((long long)value * factor + 0x800) >> 12);
}
