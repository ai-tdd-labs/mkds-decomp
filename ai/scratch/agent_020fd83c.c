// PURPOSE: Sets up this object's state handler and initial values.
// The object probably owns an embedded four-state handler at offset 0x184.
// If bit 0x80000 is already set, it leaves the object unchanged.
// Otherwise it installs a default callback when the related state bits are clear.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object020fd83c {
    u8 unused_000[0x74];
    u32 flags;
    u8 unused_078[0xa8];
    void (*field_120)(void);
    u8 unused_124[8];
    u32 field_12c;
    u32 field_130;
    u8 unused_134[0x4c];
    void (*field_180)(void);
    u16 field_194;
    u16 field_196;
    u8 stateHandler[8];
} Object020fd83c;

extern const u8 data_0216c714[];
extern void func_020fdae8(void);
extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);

void func_020fd83c(Object020fd83c *object)
{
    if (object->flags & 0x80000) {
        return;
    }

    StateDualHandler_Create(object->stateHandler, data_0216c714, 4, object);

    if (!(object->flags & 0x180000)) {
        object->field_120 = func_020fdae8;
    }

    object->field_194 = 1;
    object->field_196 = 1;
    object->field_180 = func_020fdae8;
    object->field_130 = 0;
    object->field_12c = 0;
}
