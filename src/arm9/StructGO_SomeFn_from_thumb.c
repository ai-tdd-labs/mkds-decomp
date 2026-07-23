// PURPOSE: Adds an object to the global object list and initializes it.
// The object stores two caller words, a small payload, and a mode-dependent field.
// It probably forms part of a linked list managed with interrupts disabled.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructGO {
    void *value0;
    void *value4;
    unsigned char payload[0x20];
    struct StructGO *next;
    void *value2C;
    u16 value30;
    u16 isDefault;
} StructGO;

extern int Os_DisableIrq(void);
extern void Os_RestoreIrq(int state);
extern void SetGlobalGO_from_thumb(StructGO *object);
extern StructGO *GetGlobalGO_from_thumb(void);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);

int StructGO_SomeFn_from_thumb(StructGO *object, void *value0,
                                const void *payload, void *value2C,
                                void *value4, u16 value30)
{
    StructGO *tail;
    int irq;

    irq = Os_DisableIrq();
    if (GetGlobalGO_from_thumb() == 0) {
        SetGlobalGO_from_thumb(object);
    } else {
        tail = GetGlobalGO_from_thumb();
        while (tail->next != 0)
            tail = tail->next;
        tail->next = object;
    }

    if (value2C == 0) {
        object->isDefault = 1;
    } else {
        object->value2C = value2C;
        object->isDefault = 0;
    }
    object->next = 0;
    object->value0 = value0;
    object->value4 = value4;
    object->value30 = value30;
    if (payload != 0) {
        Mem_CpuCopy8(payload, object->payload, 0x20);
    } else {
        Mem_CpuFill8(object->payload, 0, 0x20);
    }
    Os_RestoreIrq(irq);
    return 1;
}
