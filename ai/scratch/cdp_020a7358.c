extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadSanboMapObject(void);
extern void func_020a79c4(void);
extern void func_020a7eb0(void);

void Maybe_helper_0a7358(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadSanboMapObject,
                                       (void *)func_020a79c4,
                                       (void *)func_020a7eb0);
}
