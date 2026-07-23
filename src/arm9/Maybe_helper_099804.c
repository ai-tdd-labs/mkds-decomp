extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadKinoHouse2MapObject(void);
extern void Maybe_helper_099828(void *a1, void *a2);
extern void Maybe_get_17b128(void);

void Maybe_helper_099804(void)
{
    CreateAllocateMapObject_from_thumb(LoadKinoHouse2MapObject, Maybe_helper_099828, Maybe_get_17b128);
}
