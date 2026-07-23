extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadOlgPipe1MapObject(void);
extern void Maybe_helper_09a3bc(void);
extern void Maybe_get_17b14c(void);

void Maybe_helper_09a398(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadOlgPipe1MapObject,
                                       (void *)Maybe_helper_09a3bc,
                                       (void *)Maybe_get_17b14c);
}
