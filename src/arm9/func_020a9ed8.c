// PURPOSE: Creates a sub-object from four supplied parameters.
// This wrapper probably supplies a shared Struct78Sub configuration object.
// It forwards the four caller values to the creation routine unchanged.

extern char data_0217b280[];
extern void Struct78Sub_Create_from_thumb(void *config, void *arg0, void *arg1,
                                           void *arg2, void *arg3);

void func_020a9ed8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    Struct78Sub_Create_from_thumb(data_0217b280, arg0, arg1, arg2, arg3);
}
