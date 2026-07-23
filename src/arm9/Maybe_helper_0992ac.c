extern void CreateAllocateMapObject_from_thumb(void *load, void *draw, void *destroy);
extern void LoadMiniDokanMapObject(void);
extern void Maybe_helper_0992d0(void *a1, void *a2);
extern void Maybe_get_17b160(void);

void Maybe_helper_0992ac(void)
{
    CreateAllocateMapObject_from_thumb(LoadMiniDokanMapObject, Maybe_helper_0992d0, Maybe_get_17b160);
}
