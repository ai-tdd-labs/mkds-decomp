// PURPOSE: Reports whether racing has ended or the start countdown is late.
// It takes no arguments and returns one when either race condition is true.
// The display-mode check probably identifies the pre-race screen.

#pragma optimize_for_size on

extern int IsRaceEnded(void);
extern int GetDisplayMode_0(void);
extern int GetRaceStartCountdown(void);

int func_020b2bc8(void)
{
    return IsRaceEnded() ||
           (GetDisplayMode_0() == 2 && GetRaceStartCountdown() > 0xf0);
}
