/*
 * PURPOSE: Creates a map-object manager with no getter callback, flags it as active, and registers it.
 *
 * Calls the generic map-object manager creator with a load callback
 * (func_02098d04), an update/init callback (func_02098b68), and no getter
 * (0). The returned manager pointer is stored in the global slot
 * data_0217b114, its field at offset 0x1c is set to 1 (mark active), and the
 * slot is then registered via func_020d49d8. Returns the stored manager
 * pointer, re-read from the global.
 */

typedef struct MapObjectManager {
    unsigned char pad_0x00[0x1c];
    int active;
} MapObjectManager;

extern MapObjectManager *func_0209bf1c(void *load_cb, void *cb1, void *cb2);
extern void func_020d49d8(void *slot);
extern void func_02098d04(void);
extern void func_02098b68(void);
extern MapObjectManager *data_0217b114;

void *func_02098374(void)
{
    /* create the manager (no getter callback) and remember it in the global slot */
    data_0217b114 = func_0209bf1c((void *)func_02098d04, (void *)func_02098b68, 0);
    /* mark it active */
    data_0217b114->active = 1;
    /* register the slot (address of the global) */
    func_020d49d8(&data_0217b114);
    /* return via a fresh read of the global (ROM reloads it from the pool) */
    return data_0217b114;
}
