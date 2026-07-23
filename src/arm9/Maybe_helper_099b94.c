extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadDeTree1MapObject(void);
extern void Maybe_helper_099bb8(void *a1, void *a2);
extern void Maybe_get_17b154(void);

void Maybe_helper_099b94(void)
{
    CreateAllocateMapObject_from_thumb(LoadDeTree1MapObject, Maybe_helper_099bb8, Maybe_get_17b154);
}
