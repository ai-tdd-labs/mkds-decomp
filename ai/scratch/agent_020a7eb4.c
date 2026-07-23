/* PURPOSE: Load the "sanbo" (island) map object's two model pieces and mark both with polygon id 0x3f. */
extern int data_02167920;
extern int data_02167930;
extern void *data_0217b228;
extern void *data_0217b22c;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadSanboMapObject(void *a0) {
    data_0217b228 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167920);
    data_0217b22c = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167930);
    StructMapObject_MaybeSetPolygonId(data_0217b228, 0x3f);
    StructMapObject_MaybeSetPolygonId(data_0217b22c, 0x3f);
}
