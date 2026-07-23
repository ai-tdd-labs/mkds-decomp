// PURPOSE: Allocates and initializes a small callback object.
//
// The first four arguments populate callback or configuration slots.
// The final probably-small configuration value is copied into the object.

typedef unsigned short u16;

typedef struct CallbackObject {
    void *field_00;
    void *field_04;
    unsigned char unknown_08[0x10];
    void *field_18;
    unsigned int field_1c;
    void *field_20;
} CallbackObject;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

CallbackObject *CreateAllocateSomeObject_from_thumb(
    void *field_00, void *field_04, void *field_18, void *field_20, u16 field_1c)
{
    CallbackObject *object;

    /* This first lookup probably performs a required context-side effect. */
    (void)ExecutionContext_GetHeapHandle(GetActiveExecutionContext());
    object = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x40);
    object->field_00 = field_00;
    object->field_04 = field_04;
    object->field_20 = field_20;
    object->field_1c = field_1c;
    object->field_18 = field_18;
    return object;
}
