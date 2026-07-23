// PURPOSE: Starts a scene sound sequence only once.
// The argument is probably the scene sequence identifier.
// A bit in the shared scene state prevents the sequence from restarting.

typedef struct ExecutionState {
    unsigned char pad_00[0x1c];
    int unknown_flag : 1;
    int scene_sseq_started : 1;
} ExecutionState;

extern ExecutionState *data_021759d0;
extern void LoadSomeSseq(void *a0, int a1, int a2);

void SetSomeSceneSseqId(int scene)
{
    if (data_021759d0->scene_sseq_started != 0) {
        return;
    }

    data_021759d0->scene_sseq_started = 1;
    LoadSomeSseq((unsigned char *)data_021759d0 + 8, scene, 0xff);
}
