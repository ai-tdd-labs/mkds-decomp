// PURPOSE: Passes text settings to the shared text routine.
// It forwards ten integer settings, a signed byte setting, and a final zero.
// The exact meaning of these settings is probably part of the text renderer.

extern void G2d_Text_SomeFn_2_from_thumb(
    int, int, int, int, int, int, int, int, int, int, int, int);

void G2d_Text_SomeFn_5_from_thumb(
    int arg0, int arg1, int arg2, int arg3, int arg4, int arg5,
    int arg6, int arg7, int arg8, int arg9, signed char arg10)
{
    G2d_Text_SomeFn_2_from_thumb(
        arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, 0);
}
