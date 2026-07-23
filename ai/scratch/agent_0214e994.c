// PURPOSE: Applies touch-screen calibration to raw stylus readings.
// A null parameter disables calibrated coordinates.
// Nonzero axis sizes are converted into scale factors with the hardware divider.
// The shared touch-panel state is marked calibrated after both axes are updated.

typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

#define reg_CP_DIVCNT       (*(volatile u16 *)0x04000280)
#define reg_CP_DIV_NUMER_L  (*(volatile u32 *)0x04000290)
#define reg_CP_DIV_DENOM    (*(volatile u64 *)0x04000298)
#define reg_CP_DIV_RESULT_L (*(volatile u32 *)0x040002a0)

typedef struct TPCalibrateParam {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef struct TouchPanelState {
    unsigned char unknown_00[0x18];
    s32 x0;
    s32 xDotSize;
    s32 xScale;
    s32 y0;
    s32 yDotSize;
    s32 yScale;
    u16 calibrated;
} TouchPanelState;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 enabled);
extern TouchPanelState data_021803d8;

void UseSomeCalibrationStuff(const TPCalibrateParam *calibrate)
{
    u32 enabled;

    if (calibrate == 0) {
        data_021803d8.calibrated = 0;
        return;
    }

    enabled = Os_DisableIrq();

    if (calibrate->xDotSize != 0) {
        reg_CP_DIVCNT = 0;
        reg_CP_DIV_NUMER_L = 0x10000000;
        reg_CP_DIV_DENOM = (u32)calibrate->xDotSize;

        data_021803d8.x0 = calibrate->x0;
        data_021803d8.xDotSize = calibrate->xDotSize;

        while (reg_CP_DIVCNT & 0x8000) {
        }
        data_021803d8.xScale = reg_CP_DIV_RESULT_L;
    } else {
        data_021803d8.x0 = 0;
        data_021803d8.xDotSize = 0;
        data_021803d8.xScale = 0;
    }

    if (calibrate->yDotSize != 0) {
        reg_CP_DIVCNT = 0;
        reg_CP_DIV_NUMER_L = 0x10000000;
        reg_CP_DIV_DENOM = (u32)calibrate->yDotSize;

        data_021803d8.y0 = calibrate->y0;
        data_021803d8.yDotSize = calibrate->yDotSize;

        while (reg_CP_DIVCNT & 0x8000) {
        }
        data_021803d8.yScale = reg_CP_DIV_RESULT_L;
    } else {
        data_021803d8.y0 = 0;
        data_021803d8.yDotSize = 0;
        data_021803d8.yScale = 0;
    }

    Os_RestoreIrq(enabled);
    data_021803d8.calibrated = 1;
}
