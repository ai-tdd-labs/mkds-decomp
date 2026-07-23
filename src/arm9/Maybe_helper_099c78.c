extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadSnowTree1MapObject(void);
extern void Maybe_helper_099c9c(void *a1, void *a2);
extern void Maybe_get_17b168(void);

void Maybe_helper_099c78(void)
{
    CreateAllocateMapObject_from_thumb(LoadSnowTree1MapObject, Maybe_helper_099c9c, Maybe_get_17b168);
}
