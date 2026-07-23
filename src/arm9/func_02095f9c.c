/* PURPOSE: Creates some kind of task/object via func_0209bf70 and sets its
 * field at offset 0x28 to a fixed value (0x1b0).
 * Calls func_0209bf70 with a fixed set of arguments: three function/data
 * pointers (func_0209702c, func_02096f54, func_02096df0), a zero, and two
 * extra stack args (1 and 0x16d). The returned pointer (probably a newly
 * created task/heap object) then has its field at offset 0x28 set to
 * 0x1b0 (probably a priority or size value).
 */

extern void *func_0209bf70(void *a0, void *a1, void *a2, int a3, int a4, int a5);
extern void func_0209702c(void);
extern void func_02096f54(void);
extern void func_02096df0(void);

struct Task28 {
    unsigned char pad[0x28];
    int field_0x28;
};

void func_02095f9c(void)
{
    struct Task28 *obj = (struct Task28 *)func_0209bf70(
        (void *)func_0209702c,
        (void *)func_02096f54,
        (void *)func_02096df0,
        0,
        1,
        0x16d);

    obj->field_0x28 = 0x1b0;
}
