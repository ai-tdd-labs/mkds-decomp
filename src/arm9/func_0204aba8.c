// PURPOSE: Stops the scene sound state when it is running.
// This routine takes no arguments and returns no value.
// It probably releases the sound state stored inside the shared system context.
// It does nothing while another control flag is set or the sound is not running.

typedef struct ExecutionState {
    unsigned char padding_00[8];
    unsigned char padding_08[0x14];
    int unknown_flag : 1;
    int scene_sseq_started : 1;
} ExecutionState;

extern ExecutionState *data_021759d0;
extern void func_0210dc7c(void *holder);

void func_0204aba8(void)
{
    ExecutionState *state = data_021759d0;

    if (state->unknown_flag) {
        return;
    }

    if (!state->scene_sseq_started) {
        return;
    }

    func_0210dc7c((unsigned char *)state + 8);
    data_021759d0->scene_sseq_started = 0;
}
