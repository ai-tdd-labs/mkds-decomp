extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadCowMapObject(void);
extern void func_020918cc(void);
extern void Maybe_get_17b0bc(void);

void Maybe_helper_0918a8(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadCowMapObject,
                                       (void *)func_020918cc,
                                       (void *)Maybe_get_17b0bc);
}
