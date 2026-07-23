/*
 * PURPOSE: Sets up an object's three-state handler and initial flags.
 * The object probably owns an embedded state controller at offset 0x80.
 * It attaches the controller to a shared state table, then initializes two flags.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Object020ec884 {
    u8 unused_000[0x80];
    u8 stateHandler;
    u8 unused_081[0x0f];
    u16 field_090;
    u16 field_092;
} Object020ec884;

extern const u8 data_0216c414[];

extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);

void func_020ec884(Object020ec884 *object)
{
    // PURPOSE: Sets up an object's three-state handler and initial flags.
    StateDualHandler_Create(&object->stateHandler, data_0216c414, 3, object);
    object->field_090 = 0;
    object->field_092 = 1;
}
