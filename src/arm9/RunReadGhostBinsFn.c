// PURPOSE: Starts reading the saved ghost race data.
// The argument is probably the destination buffer for the loaded ghost data.
// It records that buffer, enables the save-data service, queues the worker,
// and marks the worker task as pending.

typedef struct SaveDataHolder {
    unsigned char unknown_00[0x40];
    void *ghostData;
} SaveDataHolder;

typedef struct SaveWorkerState {
    unsigned char unknown_00[0xf8];
    unsigned int taskPending;
} SaveWorkerState;

extern SaveDataHolder *data_0217aa08;
extern SaveWorkerState *data_0217aa0c;

extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void WorkerInsertTask(void (*task)(void));
extern void Task_ReadGhostBins(void);

void RunReadGhostBinsFn(void *ghostData)
{
    data_0217aa08->ghostData = ghostData;
    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(Task_ReadGhostBins);
    data_0217aa0c->taskPending = 1;
}
