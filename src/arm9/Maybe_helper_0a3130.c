extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadBalloonMapObject(void);
extern void func_020a3948(void);
extern void func_020a3e38(void);

void Maybe_helper_0a3130(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadBalloonMapObject,
                                       (void *)func_020a3948,
                                       (void *)func_020a3e38);
}
