// PURPOSE: Creates the puddle map object.
// The owner supplies the map-object context.
// This probably keeps the loaded puddle model for later use.

extern int data_0216745c;
extern void *data_0217b194;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);

void func_0209ec18(void *a0) {
    data_0217b194 = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216745c);
}
