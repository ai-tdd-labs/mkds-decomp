// PURPOSE: Converts a valid calendar date into its day number.
// The input probably stores a year, month, day, and weekday as four integers.
// Invalid dates return -1; leap years add the extra day after February.

typedef unsigned int u32;

typedef struct CalendarDate {
    u32 year;
    u32 month;
    u32 day;
    int weekday;
} CalendarDate;

extern int data_0216f26c[];
extern int IsLeapYear_from_thumb(u32 year);

int func_021522a0(CalendarDate *date)
{
    u32 year;
    u32 month;
    u32 day;
    int weekday;
    int result;

    year = date->year;
    if (year >= 100) {
        return -1;
    }

    month = date->month;
    if (month < 1) {
        return -1;
    }
    if (month > 12) {
        return -1;
    }

    day = date->day;
    if (day < 1) {
        return -1;
    }
    if (day > 31) {
        return -1;
    }

    weekday = date->weekday;
    if (weekday >= 7) {
        return -1;
    }

    if (month < 1) {
        return -1;
    }
    if (month > 12) {
        return -1;
    }

    result = (int)day - 1;
    result += data_0216f26c[month];
    if (month >= 3 && IsLeapYear_from_thumb(year) != 0) {
        result++;
    }
    return (int)(year * 365) + result + ((year + 3) >> 2);
}
