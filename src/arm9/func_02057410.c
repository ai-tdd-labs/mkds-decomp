// PURPOSE: Clears one flag in the selected course's ghost-data byte.
// The argument probably identifies a course segment.
// The function locates its byte, then clears the flag selected by the segment modulo eight.

extern unsigned char *GetGhostDataByteByCourse_from_thumb(int course);
extern int _s32_div_f(int dividend, int divisor);

void func_02057410(int course)
{
    unsigned char *byte = GetGhostDataByteByCourse_from_thumb(course);
    *byte &= ~(1 << (unsigned char)(course % 8));
}
