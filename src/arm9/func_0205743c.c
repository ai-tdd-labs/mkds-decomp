// PURPOSE: Checks whether a ghost exists for a course.
// The course number selects a stored flag byte and bit.
// It returns one when that bit is present, and probably zero otherwise.

extern unsigned char *GetGhostDataByteByCourse_from_thumb(int course);
extern int _s32_div_f(int dividend, int divisor);

int func_0205743c(int course)
{
    unsigned char *byte = GetGhostDataByteByCourse_from_thumb(course);

    if (*byte & (1 << (unsigned char)(course % 8)))
        return 1;
    return 0;
}
