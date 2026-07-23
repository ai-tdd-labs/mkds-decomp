// PURPOSE: Refreshes and returns the active HD look-at object.
// The two global objects are probably updated in sequence before the active one is kept.
// The returned pointer probably targets data within that active object.

extern void *data_0217acb4;
extern void *data_0217acb8;
extern void StructHD_SomeFn_0(void *a0);
extern void StructHD_SomeLookAt(void *a0);

void *SomeLookAtHD3(void) {
    StructHD_SomeFn_0(data_0217acb8);
    StructHD_SomeLookAt(data_0217acb8);
    data_0217acb4 = data_0217acb8;
    return (char *)data_0217acb8 + 0x30;
}
