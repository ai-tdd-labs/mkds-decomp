/*
 * PURPOSE: Creates a game object of type 0x18d and tags it with ID 0x196.
 *
 * Calls the object-spawn helper func_0209bf70 with an update callback
 * (func_0209ddec), a render/init callback (func_0209dd44), flags 0 and 1,
 * and stack args 0 and 0x18d (probably the object type/size code).
 * Then writes 0x196 (probably an object/actor ID) into field +0x28 of the
 * returned object. Pool words 0x18d and 0x196 have no relocs, so they are
 * plain constants.
 */

typedef struct SpawnedObj {
    int unk00[10];        /* +0x00..+0x27: unknown */
    int objectId;         /* +0x28: set to 0x196 by this function */
} SpawnedObj;

extern SpawnedObj *func_0209bf70(void *updateFn, void *drawFn, int a2, int a3, int a4, int a5);

extern void func_0209ddec(void);
extern void func_0209dd44(void);

void func_0209d800(void)
{
    SpawnedObj *obj = func_0209bf70(func_0209ddec, func_0209dd44, 0, 1, 0, 0x18d);
    obj->objectId = 0x196;
}
