// PURPOSE: Starts the shared AT task after saving its input object.
// The input is probably retained by the shared AT work object.
// It enables the related system flag, queues the fixed task, and marks it active.

typedef struct {
    char pad_00[0x40];
    void *input;
} ATWork;

typedef struct {
    char pad_00[0xF8];
    int active;
} ATState;

extern ATWork *data_0217aa08;
extern ATState *data_0217aa0c;
extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void Task_StructFXRelated(void);
extern void WorkerInsertTask(void (*task)(void));

void RunSomeATFunction(void *input) {
    data_0217aa08->input = input;
    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(Task_StructFXRelated);
    data_0217aa0c->active = 1;
}
