// PURPOSE: Resets a sound-related global after updating its saved state.
// The argument probably points to a record whose field at offset 0x10 is
// passed to the state-update routine.  The function then clears a shared
// global pointer or value.

typedef struct SoundStateHolder {
    char padding_00[0x10];
    void *savedState;
} SoundStateHolder;

extern void func_0210e434(void *state);
extern int data_0217d060;

void func_0210dc7c(SoundStateHolder *holder)
{
    func_0210e434(holder->savedState);
    data_0217d060 = 0;
}
