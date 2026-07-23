extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadCrossTree1MapObject(void);
extern void Maybe_helper_09a110(void);
extern void Maybe_get_17b11c(void);

void Maybe_helper_09a0ec(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadCrossTree1MapObject,
                                       (void *)Maybe_helper_09a110,
                                       (void *)Maybe_get_17b11c);
}
