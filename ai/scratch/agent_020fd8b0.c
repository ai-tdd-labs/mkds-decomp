// PURPOSE: Starts this object's state handler and enables its active flags.
// The object probably owns a four-state handler at offset 0x184.
// It skips setup when the handler state is already 2, then returns success.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object020fd8b0 {
    u8 pad_000[0x74];
    u32 flags_074;
    u16 flags_078;
    u8 pad_07a[0x120 - 0x7a];
    void (*field_120)(void);
    u8 pad_124[0x184 - 0x124];
    u8 stateHandler[1];
    u8 pad_185[0x192 - 0x185];
    u16 field_192;
    u16 field_194;
    u16 field_196;
} Object020fd8b0;

extern const u8 data_0216c714[];
extern void func_020fdae8(void);
extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);

int func_020fd8b0(Object020fd8b0 *object)
{
    if (object->field_192 != 2) {
        StateDualHandler_Create(object->stateHandler, data_0216c714, 4, object);
        object->field_194 = 2;
        object->field_196 = 1;
        if ((object->flags_074 & 0x180000) == 0) {
            object->field_120 = func_020fdae8;
        }
        object->flags_074 &= ~0x8000;
        object->flags_074 |= 0x80000;
        object->flags_078 &= ~0x4000;
    }
    return 1;
}
