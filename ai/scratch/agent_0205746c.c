// PURPOSE: Marks a course as having a personal ghost.
// The course index selects one bit in the probably persistent ghost-presence map.
// The map byte is returned by the course lookup helper.

extern unsigned char *GetGhostDataByteByCourse_from_thumb(int course);
extern int _s32_div_f(int dividend, int divisor);

void MaybeSetPersonalGhostForCoursePresent_from_thumb(int course)
{
    unsigned char *presence = GetGhostDataByteByCourse_from_thumb(course);

    /* The runtime division helper leaves the remainder in r1. */
    *presence |= 1 << (unsigned char)(course % 8);
}
