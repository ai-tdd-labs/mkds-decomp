extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadOsaTree1cMapObject(void);
extern void Maybe_helper_0999f0(void *a1, void *a2);
extern void Maybe_get_17b12c(void);

void Maybe_helper_0999cc(void)
{
    CreateAllocateMapObject_from_thumb(LoadOsaTree1cMapObject, Maybe_helper_0999f0, Maybe_get_17b12c);
}
