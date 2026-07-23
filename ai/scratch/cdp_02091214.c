extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadSmanBottomMapObject(void);
extern void func_020915c0(void);
extern void Maybe_get_17b0b4(void);

void Maybe_helper_091214(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadSmanBottomMapObject,
                                       (void *)func_020915c0,
                                       (void *)Maybe_get_17b0b4);
}
