// PURPOSE: Updates the timer values for a requested interval.
// The input selects the interval after a two-step adjustment.
// The values probably control a fixed 30-unit timing cycle.

extern int _s32_div_f(int dividend, int divisor);

typedef struct {
    int interval;
    int step;
    int duration;
} TimingValues;

extern TimingValues data_0216fdf8;

void func_0200c448(int interval)
{
    data_0216fdf8.interval = interval - 2;
    data_0216fdf8.step = _s32_div_f(30, interval - 2);
    data_0216fdf8.duration = 30;
}
