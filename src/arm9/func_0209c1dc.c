/* PURPOSE: Creates a game object with its three callback functions and marks it with flags 0x1cf.
 *
 * No arguments. Allocates a 0x40-byte object via CreateAllocateSomeObject
 * (passing three function pointers: probably update func_0209c9fc,
 * render func_0209c964 and destroy func_0209c8b0, plus two 1-constants
 * that end up at object offsets 0x20 and 0x1c), then writes the constant
 * 0x1cf into the object's field at offset 0x28 (probably a flag bitmask).
 */

/* the three callbacks stored into the new object (roles uncertain) */
extern void func_0209c9fc(void);
extern void func_0209c964(void);
extern void func_0209c8b0(void);

typedef struct {
    char pad_00[0x28];
    int flags;              /* 0x28: set to 0x1cf right after creation */
} CallbackObject;

/* thumb veneer for the allocator: args go to obj+0x00,+0x04,+0x18,+0x20 and stack arg to +0x1c */
extern CallbackObject *CreateAllocateSomeObject_from_thumb(void *cb1, void *cb2, void *cb3, int a4, int a5);

void func_0209c1dc(void)
{
    CallbackObject *obj = CreateAllocateSomeObject_from_thumb(
        (void *)func_0209c9fc, (void *)func_0209c964, (void *)func_0209c8b0, 1, 1);
    obj->flags = 0x1cf;     /* 0x1cf is not ARM-immediate encodable -> literal pool, as in ROM */
}
