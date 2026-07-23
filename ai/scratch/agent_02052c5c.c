// PURPOSE: Generates a nonzero random seed from the current clock and system tick.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long long u64;

extern void GetCurrentTime(void *time);
extern u32 OS_GetTickLo(void);

u16 func_02052c5c(void)
{
    int time[3];
    int hour;
    u16 seconds;
    u64 value;

    GetCurrentTime(time);
    hour = time[0];
    if (hour >= 18) {
        hour -= 18;
    }

    seconds = (u16)((hour * 60 + time[1]) * 60 + time[2]);
    value = (u64)((u32)seconds << 16);
    value |= OS_GetTickLo();
    value = value * 0x5d588b656c078965ULL + 0x269ec3ULL;
    return (u16)((value >> 48) | 0x8000);
}
