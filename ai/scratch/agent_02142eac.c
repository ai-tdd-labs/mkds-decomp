// PURPOSE: Updates and returns a clock-based counter.

extern unsigned int data_0216f06c;
extern void Rtc_Initialize(void);
extern int Rtc_GetTime(void *time);

unsigned short func_02142eac(void)
{
    unsigned int time[3];

    if (data_0216f06c == 0x10000) {
        Rtc_Initialize();
        if (Rtc_GetTime(time) == 0) {
            data_0216f06c = (unsigned short)(time[2] + (time[1] << 8));
        }
    }

    return data_0216f06c = (unsigned short)(data_0216f06c + 1);
}
