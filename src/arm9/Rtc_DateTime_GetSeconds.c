// PURPOSE: Converts a date and time into a total number of seconds.
// The date and time objects are probably RTC values.
// Returns -1 if either value cannot be converted.

extern int Rtc_Date_GetDays(void *date);
extern int Rtc_Time_GetSeconds(void *time);

long long Rtc_DateTime_GetSeconds(void *date, void *time)
{
    int days = Rtc_Date_GetDays(date);
    int seconds;

    if (days == -1) {
        return -1;
    }

    seconds = Rtc_Time_GetSeconds(time);
    if (seconds == -1) {
        return -1;
    }

    return (long long)days * 86400 + seconds;
}
