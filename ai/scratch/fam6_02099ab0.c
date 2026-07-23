extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadOlaTree1cMapObject(void);
extern void Maybe_helper_099ad4(void *a1, void *a2);
extern void Maybe_get_17b130(void);

void Maybe_helper_099ab0(void)
{
    CreateAllocateMapObject_from_thumb(LoadOlaTree1cMapObject, Maybe_helper_099ad4, Maybe_get_17b130);
}
