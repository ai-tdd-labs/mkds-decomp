/* PURPOSE: Halve and eighth a global position vector into two shared globals, then hand the object off to another routine.
 */

typedef struct { int x, y, z; } VecFx32;

typedef struct {
    char pad0[0x24];
    VecFx32 f24;   /* offset 0x24 */
} HD4;

extern HD4 *GetGlobalHD4(void);
extern void StructMapObject_SomeFn_9(void *obj, int val);

extern VecFx32 data_0217b214;
extern VecFx32 data_0217b208;
extern int data_0217b204;

void func_020a3e38(void *obj)
{
    HD4 *hd4 = GetGlobalHD4();

    data_0217b214.x = hd4->f24.x >> 1;
    data_0217b214.y = hd4->f24.y >> 1;
    data_0217b214.z = hd4->f24.z >> 1;

    data_0217b208.x = hd4->f24.x >> 3;
    data_0217b208.y = hd4->f24.y >> 3;
    data_0217b208.z = hd4->f24.z >> 3;

    StructMapObject_SomeFn_9(obj, data_0217b204);
}
