/*
 * PURPOSE: Creates the Pakkun (Piranha Plant) Z-head map-object manager, flags it active, and registers it.
 *
 * No arguments. Allocates/creates the map-object manager for the Pakkun
 * Z-head, passing three callbacks: the loader (LoadPakkunZHeadMapObject),
 * an update/init routine (func_02098a58), and a getter (Maybe_get_17b104).
 * The freshly created manager is stored in the global slot data_0217b110,
 * its field at offset 0x1c is set to 1 (marks it active/enabled), and the
 * slot is registered via func_020d49d8 (probably adds it to a list).
 * Returns the stored manager pointer, re-read from the global.
 */

extern void *CreateAllocateMapObject_from_thumb(void *load_cb, void *cb1, void *cb2);
extern void func_020d49d8(void *slot);
extern void LoadPakkunZHeadMapObject(void);
extern void func_02098a58(void);
extern void Maybe_get_17b104(void);
extern void *data_0217b110;

void *func_020982d4(void)
{
    /* create the manager and remember it in the global slot */
    void *obj = CreateAllocateMapObject_from_thumb(LoadPakkunZHeadMapObject, func_02098a58, Maybe_get_17b104);
    data_0217b110 = obj;
    /* mark it active (field at offset 0x1c) */
    *(int *)((char *)obj + 0x1c) = 1;
    /* register the slot (address of the global) */
    func_020d49d8(&data_0217b110);
    /* return via a fresh read of the global (ROM reloads it from the pool) */
    return data_0217b110;
}
