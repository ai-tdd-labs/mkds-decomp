// PURPOSE: Passes text layout settings to the internal text routine.
// This wrapper receives nine text and layout arguments.
// It probably supplies three default values required by the lower-level renderer.

extern void G2d_Text_SomeFn_2_from_thumb(
    void *text,
    int arg1,
    int arg2,
    int width,
    int height,
    int arg5,
    int buffer_size,
    int arg7,
    void *message,
    int arg9,
    int arg10,
    int arg11);

void G2d_Text_SomeFn_1_from_thumb(
    void *text,
    int arg1,
    int arg2,
    int width,
    int height,
    int arg5,
    int buffer_size,
    int arg7,
    void *message)
{
    G2d_Text_SomeFn_2_from_thumb(
        text, arg1, arg2, width, height, arg5, buffer_size, arg7, message,
        0, -1, 1);
}
