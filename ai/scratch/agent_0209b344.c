/*
PURPOSE: Conditionally processes with func_0209b388 if a check byte is 1, then calls func_020d26f8.

Takes a pointer arg0, base pointer arg1, check byte pointer, and result byte pointer.
If the check byte == 1, calls func_0209b388 with three pointer-offsets from the base,
then calls func_020d26f8 with the original two args.
Returns the result byte value masked to u32.
*/

typedef unsigned char u8;
typedef unsigned int u32;

extern void func_0209b388(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_020d26f8(void *arg0, void *arg1);

u32 func_0209b344(void *arg0, void *arg1, u8 *check_byte_ptr, u8 *result_byte_ptr) {
    u8 check = *check_byte_ptr;
    u8 result = *result_byte_ptr;

    if (check != 1) goto end;

    func_0209b388(arg0, (u8*)arg1 + 0x80, (u8*)arg1 + 0x68, (u8*)arg1 + 0xa4);
    func_020d26f8(arg0, arg1);

end:
    return (u32)result & 0xff;
}
