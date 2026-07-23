// PURPOSE: Sets the race speed values for the current course mode.

// It prepares several fixed-point globals using the current race state.
// The final mode value is probably a race-speed setting selected by course mode.

typedef int fx32;
typedef long long fx64;

typedef struct RaceConfig {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
} RaceConfig;

extern int data_0217bd48;
extern int data_0217bd4c;
extern int data_0217bd50;
extern int data_0217bd54;
extern int *data_0217bc34;
extern int data_0217bd58;
extern RaceConfig *gRaceConfig;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx64 Multiply64(fx64 a, fx64 b);

void func_020fd264(void)
{
    fx64 a;
    fx64 b;
    fx64 product;

    data_0217bd50 = 0x18006;
    data_0217bd48 = FX_Div(0x1000, data_0217bd50);

    data_0217bd54 = 0x2148;

    a = (fx64)data_0217bd50;
    b = (fx64)*(int *)((char *)data_0217bc34 + 0x654);
    product = Multiply64(a, b);
    data_0217bd4c = (int)(product >> 12);
    data_0217bd4c = data_0217bd4c >> 12;
    data_0217bd4c = data_0217bd4c * data_0217bd4c;

    switch (gRaceConfig->field_10) {
    case 0:
        data_0217bd58 = 0xb4;
        return;
    case 1:
        data_0217bd58 = 0x96;
        return;
    default:
        data_0217bd58 = 0x78;
        return;
    }
}
