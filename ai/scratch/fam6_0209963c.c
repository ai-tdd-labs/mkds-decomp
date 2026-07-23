extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadKinoMount2MapObject(void);
extern void Maybe_helper_099660(void *a1, void *a2);
extern void Maybe_get_17b13c(void);

void Maybe_helper_09963c(void)
{
    CreateAllocateMapObject_from_thumb(LoadKinoMount2MapObject, Maybe_helper_099660, Maybe_get_17b13c);
}
