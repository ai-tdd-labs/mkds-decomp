// PURPOSE: Sets up the current scene transition state.
// It creates the state handler and clears the transition fields.
// In state one, it probably selects the active transition byte.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SceneTransitionContext {
    int state;
    u8 pad_004[0x82];
    u8 selectedTransition;
    u8 transitionValue;
    u8 pad_088[0x3cc];
    u16 flags;
    u8 pad_456[0x11c6];
    u16 field_161c;
    u8 pad_161e[4];
    u8 field_1622;
    u8 pad_1623[5];
    u8 field_1628;
    u8 pad_1629;
    u8 field_162a;
    u8 pad_162b[0x21];
    u8 field_164c;
    u8 pad_164d;
    u8 field_164e;
    u8 pad_164f[0x861];
    int field_1eb0;
} SceneTransitionContext;

extern SceneTransitionContext *data_0217aa00;
extern const u8 data_021652b0[];
extern void StateDualHandler_Create(void *handler, const void *stateTable,
                                    int count, void *owner);

void func_02059878(void)
{
    StateDualHandler_Create((u8 *)data_0217aa00 + 0x1608,
                            data_021652b0, 0x17, 0);

    data_0217aa00->field_164e = 0;
    data_0217aa00->field_161c = 0;
    data_0217aa00->field_1622 = 0;
    data_0217aa00->field_1628 = 0;
    data_0217aa00->field_162a = 0;
    data_0217aa00->field_164c = 0;

    if (data_0217aa00 != 0) {
        if (data_0217aa00->state == 1) {
            data_0217aa00->selectedTransition =
                (data_0217aa00->flags & 0x40) != 0
                    ? *((u8 *)data_0217aa00 + 0x1695)
                    : data_0217aa00->transitionValue;
        }
    }

    data_0217aa00->field_1eb0 = 0;
}
