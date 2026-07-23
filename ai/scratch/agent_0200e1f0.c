/* PURPOSE: Exits a thread and passes a value to its destructor.
 * The first argument is the thread whose saved context is replaced.
 * The second argument is passed to the destructor callback.
 * A dedicated destructor stack is used when one has been configured. */

typedef unsigned int u32;

typedef struct Arm_Context {
    u32 cpsr;
    u32 registers[24];
} Arm_Context;

typedef struct Os_Thread {
    Arm_Context context;
    int state;
} Os_Thread;

extern void *data_0216ff44;

extern void Os_DisposeCurrentThread(void *destructorArgument);
extern void Arm_Context_Create(Arm_Context *context, u32 programCounter,
                               u32 stackPointer);
extern void Arm_Context_Load(Arm_Context *context);

void Os_Thread_ExitImpl(Os_Thread *thread, void *destructorArgument)
{
    if (data_0216ff44 != 0) {
        Arm_Context_Create(&thread->context, (u32)Os_DisposeCurrentThread,
                           (u32)data_0216ff44);
        thread->context.registers[0] = (u32)destructorArgument;
        thread->context.cpsr |= 0x80;
        thread->state = 1;
        Arm_Context_Load(&thread->context);
    } else {
        Os_DisposeCurrentThread(destructorArgument);
    }
}
