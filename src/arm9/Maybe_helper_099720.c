extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadKinoMount1MapObject(void);
extern void Maybe_helper_099744(void *a1, void *a2);
extern void Maybe_get_17b120(void);

void Maybe_helper_099720(void)
{
    CreateAllocateMapObject_from_thumb(LoadKinoMount1MapObject, Maybe_helper_099744, Maybe_get_17b120);
}
