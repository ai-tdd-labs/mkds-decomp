// PURPOSE: Gets the current time and clears it if the clock read fails.
// Arguments: time points to three time words.
// Behaviour: probably leaves the clock result intact when the read succeeds.

extern int Rtc_GetTime(void *time);

void GetCurrentTime(void *time) {
    if (Rtc_GetTime(time) != 0) {
        ((int *)time)[0] = 0;
        ((int *)time)[1] = 0;
        ((int *)time)[2] = 0;
    }
}
