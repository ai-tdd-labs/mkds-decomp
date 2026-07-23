extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadShineBalloonMapObject(void);
extern void func_020ac890(void);
extern void Maybe_get_17b33c(void);

void Maybe_helper_0ac658(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadShineBalloonMapObject,
                                       (void *)func_020ac890,
                                       (void *)Maybe_get_17b33c);
}
