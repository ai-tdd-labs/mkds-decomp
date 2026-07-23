// PURPOSE: Retrieves the enabled state of the top and bottom screen backlights.
typedef unsigned short u16;

extern int Pm_GetBacklightFlags(int unused, u16 *flags);

int Pm_GetBacklightStatus(int *topBacklight, int *bottomBacklight)
{
    u16 flags;
    int result;

    result = Pm_GetBacklightFlags(0, &flags);
    if (result != 0) {
        return result;
    }

    if (topBacklight != 0) {
        *topBacklight = (flags & 8) != 0;
    }

    if (bottomBacklight == 0) {
        return result;
    }

    *bottomBacklight = (flags & 4) != 0;
    return result;
}
