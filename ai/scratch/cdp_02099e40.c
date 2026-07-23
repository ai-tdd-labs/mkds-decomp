extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadTownTree1MapObject(void);
extern void Maybe_helper_099e64(void);
extern void Maybe_get_17b124(void);

void Maybe_helper_099e40(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadTownTree1MapObject,
                                       (void *)Maybe_helper_099e64,
                                       (void *)Maybe_get_17b124);
}
