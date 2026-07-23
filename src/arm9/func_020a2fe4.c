/* PURPOSE: Allocates and initializes a small game-object record from a template.
 * Allocates 0x6c bytes via func_02100138, then asks func_0209bbfc to fill it
 * (probably some kind of object-pool/registration step). If that call fails
 * (returns 0), returns 0. Otherwise copies a 3-word vector (from the arg1
 * pointer) into two fields of the new object (offset 0xb0 and offset 4),
 * clears several fields (0xd0,0xd4,0xd8,0xdc,0xe0,0xfc), stores arg0 into
 * offset 0xa8, and returns the new object pointer.
 */
typedef struct
{
    int x, y, z;
} Vec3i;

extern void *func_02100138(int size);
extern void *func_0209bbfc(void *param);

void *func_020a2fe4(void *a0, Vec3i *a1)
{
    char *obj;

    obj = (char *)func_0209bbfc(func_02100138(0x6c));
    if (obj == 0)
    {
        return 0;
    }

    *(Vec3i *)(obj + 0xb0) = *a1;
    *(Vec3i *)(obj + 4) = *(Vec3i *)(obj + 0xb0);

    *(int *)(obj + 0xd0) = 0;
    *(int *)(obj + 0xd4) = 0;
    *(int *)(obj + 0xd8) = 0;
    *(int *)(obj + 0xdc) = 0;
    *(int *)(obj + 0xe0) = 0;
    *(void **)(obj + 0xa8) = a0;
    *(int *)(obj + 0xfc) = 0;

    return obj;
}
