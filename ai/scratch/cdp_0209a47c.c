extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadOlgMush1MapObject(void);
extern void Maybe_helper_09a4a0(void);
extern void Maybe_get_17b16c(void);

void Maybe_helper_09a47c(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadOlgMush1MapObject,
                                       (void *)Maybe_helper_09a4a0,
                                       (void *)Maybe_get_17b16c);
}
