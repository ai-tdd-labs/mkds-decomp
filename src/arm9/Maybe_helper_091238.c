extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadSmanTopMapObject(void);
extern void func_020916a0(void);
extern void Maybe_get_17b0b8(void);

void Maybe_helper_091238(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadSmanTopMapObject,
                                       (void *)func_020916a0,
                                       (void *)Maybe_get_17b0b8);
}
