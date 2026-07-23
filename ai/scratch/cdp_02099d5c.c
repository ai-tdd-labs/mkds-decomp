extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadMarioTree3MapObject(void);
extern void Maybe_helper_099d80(void);
extern void Maybe_get_17b134(void);

void Maybe_helper_099d5c(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadMarioTree3MapObject,
                                       (void *)Maybe_helper_099d80,
                                       (void *)Maybe_get_17b134);
}
