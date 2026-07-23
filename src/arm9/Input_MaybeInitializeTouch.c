// PURPOSE: Initializes touch input calibration when it is available.
//
// Starts the touch-panel FIFO, then prepares a small calibration record.
// The record is probably consumed only when the preparation succeeds.

extern void Os_InitializeTouchPanelFifo(void);
extern int ComputeSomeScreenCalibrationStuff(void *a0);
extern void UseSomeCalibrationStuff(void *a0);

void Input_MaybeInitializeTouch(void) {
    int calibration[3];

    Os_InitializeTouchPanelFifo();
    if (ComputeSomeScreenCalibrationStuff(calibration) == 0) {
        return;
    }
    UseSomeCalibrationStuff(calibration);
}
