// PURPOSE: Advances the sound work timer and starts the next sound update.
// This function takes no arguments.
// It probably advances the shared sound state every tick and resets the
// timer after four sound-work steps once the delay reaches its threshold.

typedef struct SoundWork {
    unsigned char padding_00[0x74];
    int field_74;
    short field_78;
} SoundWork;

extern SoundWork *data_0217d360;
extern void func_021187d4(void);

#pragma optimize_for_size on

void func_02118414(void)
{
    data_0217d360->field_74++;
    if (data_0217d360->field_74 >= 75) {
        data_0217d360->field_78++;
        if (data_0217d360->field_78 >= 4) {
            data_0217d360->field_78 = 0;
        }
        data_0217d360->field_74 = 0;
        func_021187d4();
    }
}
