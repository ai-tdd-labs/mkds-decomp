// PURPOSE: Gets the current date from the real-time clock.
// Arguments: a writable three-integer date buffer.
// Behaviour: probably supplies a default date when the clock read fails.

extern int Rtc_GetDate(void *time);

void GetCurrentDate(int *date)
{
    if (Rtc_GetDate(date) != 0) {
        date[0] = 5;
        date[1] = 1;
        date[2] = 1;
    }
}
