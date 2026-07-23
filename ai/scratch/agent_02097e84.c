/* Loads the flipper map object (pinball track): model + nsbtp and
 * nsbta animations. */
extern int data_0216698c;
extern int data_0216699c;
extern int data_021669ac;
extern void *data_0217b0f8;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbtp_from_thumb(void *obj, void *a1);
extern void StructMapObject_AddAnimationNsbta_from_thumb(void *obj, void *a1);

void LoadFlipperMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_0216698c);
    data_0217b0f8 = obj;
    StructMapObject_AddAnimationNsbtp_from_thumb(obj, &data_0216699c);
    StructMapObject_AddAnimationNsbta_from_thumb(data_0217b0f8, &data_021669ac);
}
