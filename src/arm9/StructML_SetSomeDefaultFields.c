// PURPOSE: Sets the standard fields for a StructML object.
//
// It passes the object and its default callback to the shared field setup
// routine. The remaining values probably select the object's usual mode.

extern void StructMLFnPtr(void);
extern void StructML_SetSomeFields(void *object, void (*callback)(void), int value2, int value3, int value4);

void StructML_SetSomeDefaultFields(void *object)
{
    StructML_SetSomeFields(object, StructMLFnPtr, 0, 6, 3);
}
