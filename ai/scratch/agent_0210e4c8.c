// PURPOSE: Saves the current sound frame state.
// The argument receives the saved state in its fourth word.
// It probably backs up the active sound frame before another sound operation.

extern void *data_0217d130;
extern int Sound_Context_BackupFrameState(void *context);

void func_0210e4c8(int *a0) {
    a0[3] = Sound_Context_BackupFrameState(data_0217d130);
}
