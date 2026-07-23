// PURPOSE: Reports whether the current timing value matches the requested value.
// The argument is compared with the shared work state's selected value.
// The return flags probably identify zero and fifteen-frame timing points.

typedef struct WorkState {
    char _000[0x10C];
    int timing_value;
    int selected_value;
} WorkState;

extern WorkState *data_02174e18;
extern long long _s32_div_f(int dividend, int divisor);

int func_020290ac(int value)
{
    int result = 0;

    if (data_02174e18->selected_value == value) {
        result |= data_02174e18->timing_value == 0;

        {
            int timing_flag = 0;
            if (data_02174e18->timing_value >= 60) {
                long long division = _s32_div_f(
                    data_02174e18->timing_value - 60, 15);
                if ((int)(division >> 32) == 0) {
                    timing_flag = 1;
                }
            }
            result |= timing_flag;
        }
    }
    return result;
}
