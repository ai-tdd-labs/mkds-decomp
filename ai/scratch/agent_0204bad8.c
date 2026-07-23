// PURPOSE: Starts the shared worker thread.
// This function has no arguments and returns no value.
// It clears two worker-state fields before creating the thread.
// The worker entry and state layout are probably shared with nearby thread code.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct WorkerState {
    u8 padding[0x4c0];
    u32 previousState;
    u32 state;
} WorkerState;

extern void Os_Thread_Create(void *thread, void (*entry)(void *), void *argument,
                             void *stackTop, u32 stackSize, u32 priority);
extern void Os_Thread_WakeUpDirect(void *thread);
extern void SomeThreadEntry2(void *argument);
extern WorkerState data_021759d8;

void func_0204bad8(void)
{
    data_021759d8.state = 0;
    data_021759d8.previousState = data_021759d8.state;
    Os_Thread_Create((u8 *)&data_021759d8 + 0x400, SomeThreadEntry2,
                     &data_021759d8, (u8 *)&data_021759d8 + 0x400, 0x400, 0xf);
    Os_Thread_WakeUpDirect((u8 *)&data_021759d8 + 0x400);
}
