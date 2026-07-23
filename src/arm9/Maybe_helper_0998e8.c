extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadKinoHouse1MapObject(void);
extern void Maybe_helper_09990c(void *a1, void *a2);
extern void Maybe_get_17b148(void);

void Maybe_helper_0998e8(void)
{
    CreateAllocateMapObject_from_thumb(LoadKinoHouse1MapObject, Maybe_helper_09990c, Maybe_get_17b148);
}
