extern void CreateAllocateMapObject_from_thumb(void *a0, void *a1, void *a2);
extern void LoadNsCannon1MapObject(void);
extern void Maybe_helper_09a1f4(void);
extern void Maybe_get_17b170(void);

void Maybe_helper_09a1d0(void) {
    CreateAllocateMapObject_from_thumb((void *)LoadNsCannon1MapObject,
                                       (void *)Maybe_helper_09a1f4,
                                       (void *)Maybe_get_17b170);
}
