// PURPOSE: Starts the kart state handler and marks the state as active.
// The argument is probably a kart state object with control flags and state fields.
// It creates the handler once, updates its flags, and returns success.

typedef unsigned short u16;
typedef unsigned int u32;

extern void StateDualHandler_Create(void *state, void *handler, int count, void *owner);
extern void func_020f9c6c(void *owner);
extern void func_020fc2c0(void);
extern char data_0216c6b4[];

typedef struct KartState {
    char pad_000[0x74];
    u32 flags;
    u16 flags78;
    char pad_07a[0x120 - 0x7a];
    void (*handlerFunc)(void);
    char pad_124[0x2e8 - 0x124];
    char handlerState[1];
    char pad_2e9[0x2f6 - 0x2e9];
    u16 state;
    u16 nextState;
    u16 active;
} KartState;

int func_020fade4(KartState *state)
{
    if (state->state != 7) {
        StateDualHandler_Create(state->handlerState, data_0216c6b4, 8, state);
        state->nextState = 7;
        state->active = 1;
        if ((state->flags & 0x180000) == 0) {
            state->handlerFunc = func_020fc2c0;
        }
        state->flags &= ~0x8000;
        state->flags |= 0x80000;
        func_020f9c6c(state);
        state->flags78 &= ~0x4000;
    }
    return 1;
}
