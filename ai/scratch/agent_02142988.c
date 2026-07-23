// PURPOSE: Tests whether the current wireless state matches a supplied status.

#include <stdarg.h>

typedef unsigned int u32;
typedef unsigned short u16;

extern int Wm_CheckInitialized(void);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void **data_0217eed4;

int func_02142988(int count, ...)
{
    va_list args;
    int result;

    result = Wm_CheckInitialized();
    if (result != 0) {
        return result;
    }

    DC_InvalidateRangeNoClean(data_0217eed4[0][1], 2);

    if (count == 0) {
        return 3;
    }

    result = 3;
    va_start(args, count);
    do {
        if (va_arg(args, int) == *(u16 *)data_0217eed4[0][1]) {
            result = 0;
        }
    } while (--count != 0);

    return result;
}
