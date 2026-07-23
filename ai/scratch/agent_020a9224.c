/* PURPOSE: Creates a game object with a single callback and sets two independent fixed-point fields on it.
 *
 * Allocates a 0x40-byte object via CreateAllocateSomeObject (passing
 * func_020a9de4 as the sole callback, the other two callback slots left at
 * 0, and a trailing stack arg of 1), then writes 0x190000 (a fixed-point
 * constant) into field_38 and -0x1f4000 into field_3c.
 */

extern void func_020a9de4(void);

typedef struct {
    char pad_00[0x38];
    int field_38;   /* 0x38: set to 0x190000 */
    int field_3c;   /* 0x3c: set to -0x1f4000 */
} CallbackObject;

/* thumb veneer for the allocator: args go to obj+0x00,+0x04,+0x18,+0x20 and stack arg to +0x1c */
extern CallbackObject *CreateAllocateSomeObject_from_thumb(void *cb1, void *cb2, void *cb3, int a4, int a5);

void func_020a9224(void)
{
    CallbackObject *obj = CreateAllocateSomeObject_from_thumb(
        (void *)func_020a9de4, 0, 0, 1, 1);
    obj->field_38 = 0x190000;
    obj->field_3c = -0x1f4000;
}
