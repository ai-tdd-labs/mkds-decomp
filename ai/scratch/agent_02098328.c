/*
 * PURPOSE: Sets up the Piranha Plant body objects on the track and remembers their manager.
 *
 * No arguments. Creates/allocates the map-object manager for the Pakkun
 * (Piranha Plant) body, passing three callbacks: the loader
 * (LoadPakkunBodyMapObject), an update/init routine (func_02098954), and a
 * getter (Maybe_get_17b10c). The result is stored in the global slot
 * data_0217b108, which is then registered via func_020d49d8 (probably adds
 * it to a list). Returns the stored manager pointer, re-read from the global.
 */

extern void *CreateAllocateMapObject_from_thumb(void *load_cb, void *cb1, void *cb2);
extern void func_020d49d8(void *slot);
extern void LoadPakkunBodyMapObject(void);
extern void func_02098954(void);
extern void Maybe_get_17b10c(void);
extern void *data_0217b108;

void *func_02098328(void)
{
    /* create the manager and remember it in the global slot */
    data_0217b108 = CreateAllocateMapObject_from_thumb(LoadPakkunBodyMapObject, func_02098954, Maybe_get_17b10c);
    /* register the slot (address of the global) */
    func_020d49d8(&data_0217b108);
    /* return via a fresh read of the global (ROM reloads it from the pool) */
    return data_0217b108;
}
