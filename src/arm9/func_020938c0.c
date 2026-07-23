/* PURPOSE: Creates some kind of task/object via func_0209bf70 and sets its
 * range fields at offsets 0x38 and 0x3c to fixed fixed-point values.
 * Calls func_0209bf70 with func_02093b7c as the update/constructor callback
 * pointer, two zero args, a priority of 1, a count/flag of 1, and a type/id
 * of 0x17b (a literal-pool constant, not a symbol). The returned pointer
 * (probably a newly created task/object) then has its 0x38 field set to
 * 0x32000 (probably a near value) and its 0x3c field set to -0x64000
 * (probably a far value), likely a min/max range pair.
 */

extern void *func_0209bf70(void *a0, void *a1, void *a2, int a3, int a4, int a5);
extern void func_02093b7c(void);

struct RangeObj38 {
    unsigned char pad[0x38];
    int near38;
    int far3c;
};

void func_020938c0(void)
{
    struct RangeObj38 *obj = (struct RangeObj38 *)func_0209bf70(
        (void *)func_02093b7c,
        0,
        0,
        1,
        1,
        0x17b);

    obj->near38 = 0x32000;
    obj->far3c = -0x64000;
}
