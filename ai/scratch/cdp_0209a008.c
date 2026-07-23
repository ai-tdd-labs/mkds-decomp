extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadBankTree1MapObject(void);
extern void Maybe_helper_09a02c(void);
extern void Maybe_get_17b144(void);

void Maybe_helper_09a008(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadBankTree1MapObject,
                                       (void *)Maybe_helper_09a02c,
                                       (void *)Maybe_get_17b144);
}
