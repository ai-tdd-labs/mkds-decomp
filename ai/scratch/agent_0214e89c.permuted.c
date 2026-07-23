typedef unsigned char u8;
typedef unsigned short u16;

typedef struct TouchPanelState {
    u8 unknown_00[4];
    u16 field_04;
    u16 field_06;
    u16 field_08;
    u16 field_0a;
    u8 unknown_0c[0x28];
    u16 status;
} TouchPanelState;

typedef struct TouchPanelSample {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
} TouchPanelSample;

extern u16 WaitForTPFlags(u16 flags);
extern TouchPanelState data_021803d8;

int func_0214e89c(TouchPanelSample *sample)
{
    // PURPOSE: Copies the completed touch-panel sample into the caller's output buffer.
    u16 field_06;
    u16 field_04;
    u16 field_0a;
    u16 field_08;

    WaitForTPFlags(1);
    if (data_021803d8.status & 1) {
        return 1;
    }

    field_06 = data_021803d8.field_06;
    field_04 = data_021803d8.field_04;
    sample->field_00 = field_04;
    sample->field_02 = field_06;
    field_0a = data_021803d8.field_0a;
    field_08 = data_021803d8.field_08;
    sample->field_04 = field_08;
    sample->field_06 = field_0a;
    return 0;
}
