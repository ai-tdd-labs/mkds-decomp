typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern const u8 data_02152de4[724];
#define sVolumeTable data_02152de4

u16 Maybe_helper_0218f4(s32 x) {
    int decibels = (int)x;
    if (decibels < -723)
        decibels = -723;
    else if (decibels > 0)
        decibels = 0;

    u32 resultLo = sVolumeTable[decibels + 723];
    u32 resultHi;

    if (decibels < -240) {
        resultHi = 3;
    } else {
        if (decibels < -120) {
            resultHi = 2;
        } else {
            if (decibels < -60) {
                resultHi = 1;
            } else {
                resultHi = 0;
            }
        }
    }

    return (u16)((resultHi << 8u) | resultLo);
}
