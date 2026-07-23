// PURPOSE: Initializes an object's transform, state handler, and initial state values.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Matrix4x3 {
    s32 values[12];
} Matrix4x3;

typedef struct Object020fe3d8 {
    u8 unused_000[0x13c];
    Matrix4x3 transform;
    s32 field_16c;
    s32 field_170;
    s32 field_174;
    u16 field_178;
    u16 unused_17a;
    s32 field_17c;
    s32 field_180;
    u8 stateHandler[0x14];
    s32 field_198;
    u8 unused_19c[4];
    s32 field_1a0;
} Object020fe3d8;

extern const u8 data_0216c714[];

extern void Matrix4x3_Identity(Matrix4x3 *matrix);
extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);
extern void StateDualHandler_SetState(void *handler, int state);

void func_020fe3d8(Object020fe3d8 *object)
{
    Matrix4x3_Identity(&object->transform);
    StateDualHandler_Create(object->stateHandler, data_0216c714, 4, object);
    StateDualHandler_SetState(object->stateHandler, 0);
    object->field_170 = 0x12c;
    object->field_174 = 0;
    object->field_178 = 8;
    object->field_17c = 99980001;
    object->field_180 = 0;
    object->field_16c = 0;
    object->field_1a0 = 1;
    object->field_198 = 0;
}
