extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadOpaTree1MapObject(void);
extern void Maybe_helper_09a584(void);
extern void Maybe_get_17b140(void);

void Maybe_helper_09a560(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadOpaTree1MapObject,
                                       (void *)Maybe_helper_09a584,
                                       (void *)Maybe_get_17b140);
}
