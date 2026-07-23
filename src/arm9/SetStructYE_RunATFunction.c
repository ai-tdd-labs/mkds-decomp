// PURPOSE: Starts the StructYE background task.
// The input is probably a callback stored in the active StructYE state.
// It enables save-data work, queues the StructYE task, and marks it pending.

typedef struct {
    char padding[0x40];
    void *run_at_function;
} StructYEState;

typedef struct {
    char padding[0xf8];
    int task_pending;
} StructYEWork;

extern StructYEState *data_0217aa08;
extern StructYEWork *data_0217aa0c;
extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void WorkerInsertTask(void (*task)(void));
extern void TaskFunction_StructYE(void);

void SetStructYE_RunATFunction(void *run_at_function) {
    data_0217aa08->run_at_function = run_at_function;
    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(TaskFunction_StructYE);
    data_0217aa0c->task_pending = 1;
}
