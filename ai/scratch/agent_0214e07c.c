// PURPOSE: Starts an asynchronous read of the current date.
// The three arguments are saved for the completion handler, probably as output data and a callback.
// Only one RTC date read may run at once.

typedef unsigned int u32;

typedef struct RtcDateRequest {
    int busy;
    void *arg1;
    void *arg0;
    unsigned char unknown0c[4];
    void *arg2;
    void *unknown14;
    void *unknown18;
} RtcDateRequest;

extern RtcDateRequest data_021803b0;
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern int Rtc_ReadRawDateAsync(void);

int Rtc_GetDateAsync(void *arg0, void *arg1, void *arg2)
{
    u32 state;

    state = Os_DisableIrq();
    if (data_021803b0.busy != 0) {
        Os_RestoreIrq(state);
        return 1;
    }

    data_021803b0.busy = 1;
    Os_RestoreIrq(state);

    data_021803b0.unknown14 = 0;
    data_021803b0.unknown18 = 0;
    data_021803b0.arg0 = arg0;
    data_021803b0.arg1 = arg1;
    data_021803b0.arg2 = arg2;

    if (Rtc_ReadRawDateAsync() != 0) {
        return 0;
    }
    return 3;
}
