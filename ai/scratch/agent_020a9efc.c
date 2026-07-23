// PURPOSE: Creates a Struct78Sub object using a shared template.
// Passes the caller's four values to the structure factory.
// The template pointer is stored in the ROM data pool.

extern void Struct78Sub_Create_from_thumb(void *template_data, void *arg1,
                                          void *arg2, void *arg3, void *arg4);
extern char data_0217b278[];

void func_020a9efc(void *arg1, void *arg2, void *arg3, void *arg4)
{
    Struct78Sub_Create_from_thumb(data_0217b278, arg1, arg2, arg3, arg4);
}
