/*
 * PURPOSE: Creates a game object of type 0x10e and tags it with ID 0x10f.
 *
 * Calls the object-spawn helper func_0209bf70 with an update callback
 * (func_0209b344), a render/init callback (func_0209b270), flags 0 and 2,
 * and stack args 1 and 0x10e (probably the object kind/type code).
 * Then writes 0x10f (probably an object/actor ID) into field +0x28 of the
 * returned object. Pool words 0x10e and 0x10f have no relocs, so they are
 * plain constants.
 */

typedef struct SpawnedObj {
    int unk00[10];        /* +0x00..+0x27: unknown */
    int objectId;          /* +0x28: set to 0x10f by this function */
} SpawnedObj;

extern SpawnedObj *func_0209bf70(void *updateFn, void *drawFn, int a2, int a3, int a4, int a5);

extern void func_0209b344(void);
extern void func_0209b270(void);

void func_0209a78c(void)
{
    SpawnedObj *obj = func_0209bf70(func_0209b344, func_0209b270, 0, 2, 1, 0x10e);
    obj->objectId = 0x10f;
}
