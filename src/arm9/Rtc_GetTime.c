/* PURPOSE: Reads the current time from the real-time clock.
 * time receives the clock's current time when the asynchronous request succeeds.
 * The function waits for that request to finish and returns its stored status.
 */

typedef struct {
    unsigned char unknown[0x20];
    int result;
} RtcWork;

extern RtcWork data_021803b0;

extern void Rtc_GetTimeAsync_ErrorFunction(void);
extern int Rtc_GetTimeAsync(void *time, void (*callback)(void), void *context);
extern void Rtc_WaitBusy(void);

int Rtc_GetTime(void *time)
{
    int result = Rtc_GetTimeAsync(time, Rtc_GetTimeAsync_ErrorFunction, 0);

    data_021803b0.result = result;
    if (result == 0) {
        Rtc_WaitBusy();
    }
    return data_021803b0.result;
}
