/*
PURPOSE: Initializes an object's state handler and transform.
The argument is probably a race-scene object with animation and timing state.
This creates its eight-state handler, resets its transform, copies the current
racer index, and sets the remaining initial counters and flags.
*/

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Matrix4x3 {
    s32 values[12];
} Matrix4x3;

typedef struct ObjectState {
    u8 unused_000[0x26c];
    s32 elapsedTime;
    s32 initialDelay;
    u16 enabled;
    s16 racerIndex;
    s32 transitionState;
    u8 unused_27c[4];
    u16 sequenceIndex;
    u8 unused_282[0x32];
    Matrix4x3 transform;
    s32 stateTimer;
    u8 stateHandler[8];
} ObjectState;

typedef struct GlobalRaceState {
    u8 unused_000[0x474];
    s8 racerIndex;
} GlobalRaceState;

extern const u8 data_0216c6b4[];
extern GlobalRaceState *data_0217561c;

extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int stateCount, void *owner);
extern void Matrix4x3_Identity(Matrix4x3 *matrix);

void func_020fcac0(ObjectState *object)
{
    StateDualHandler_Create(object->stateHandler, data_0216c6b4, 8, object);
    Matrix4x3_Identity(&object->transform);

    object->enabled = 1;
    object->racerIndex = data_0217561c->racerIndex;
    object->transitionState = 0;
    object->elapsedTime = 0;
    object->initialDelay = 0xdc;
    object->sequenceIndex = 0;
    object->stateTimer = 0;
}
