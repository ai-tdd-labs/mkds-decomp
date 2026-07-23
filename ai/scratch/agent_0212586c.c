// PURPOSE: Formats text into a temporary buffer and draws it with the requested layout settings.
typedef struct TextWork {
    int result0;
    int result1;
    int result2;
    unsigned char pad_0c[0x4c];
    unsigned char buffer[0x3e8];
} TextWork;

extern void G2d_Text_SomeFn_3_from_thumb(
    int, int *, int *, int *, int, void *, int, int);
extern void G2d_Text_SomeFn_4_from_thumb(
    int, int, int *, int, int, int, int, int, int, int, int, void *, int,
    int, int);

void G2d_Text_SomeFn_2_from_thumb(
    int arg0, int arg1, int arg2, int arg3, int arg4, int arg5,
    int arg6, int arg7, int arg8, int arg9, signed char arg10, int arg11)
{
    TextWork work;

    G2d_Text_SomeFn_3_from_thumb(
        arg0, &work.result0, &work.result2, &work.result1,
        arg8, work.buffer, arg9, arg10);
    G2d_Text_SomeFn_4_from_thumb(
        arg0, work.result0, &work.result2, work.result1,
        arg1, arg2, arg3, arg4, arg5, arg6, arg7, work.buffer,
        arg9, arg10, arg11);
}
