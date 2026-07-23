// PURPOSE: Validates the saved touch-screen calibration and clears invalid output values.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ScreenCalibration {
    u8 padding[0x58];
    u16 value0;
    u16 value1;
    u8 value2;
    u8 value3;
    u16 value4;
    u16 value5;
    u8 value6;
    u8 value7;
} ScreenCalibration;

extern int MaybeCheckScreenCalibration(u16 *output, u16 value0, u16 value1,
                                       u8 value2, u8 value3, u16 value4,
                                       u16 value5, u8 value6, u8 value7);

int ComputeSomeScreenCalibrationStuff(u16 *output)
{
    ScreenCalibration *calibration;
    u16 value0;
    u16 value1;
    u8 value2;
    u16 value4;
    u16 value5;
    u8 value3;
    u8 value6;
    u8 value7;

    calibration = (ScreenCalibration *)0x027ffc80;
    value0 = calibration->value0;
    value1 = calibration->value1;
    value2 = calibration->value2;
    value3 = calibration->value3;
    value4 = calibration->value4;
    value5 = calibration->value5;
    value6 = calibration->value6;
    value7 = calibration->value7;

    if (value0 != 0 || value4 != 0 || value1 != 0 || value5 != 0) {
        if (MaybeCheckScreenCalibration(output, value0, value1, value2,
                                        value3, value4, value5, value6,
                                        value7) == 0) {
            goto return_success;
        }
    }

    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    output[3] = 0;

return_success:
    return 1;
}
