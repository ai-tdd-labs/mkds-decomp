// PURPOSE: Starts the task that writes the save data header.
// Enables the save-data flag, then schedules the header-writing task.
// The worker state is probably used to record that a task is pending.

typedef struct SaveWorkerState {
    unsigned char unknown_00[0xf8];
    unsigned int taskPending;
} SaveWorkerState;

extern SaveWorkerState *data_0217aa0c;

extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void WorkerInsertTask(void (*task)(void));
extern void Task_WriteSaveDataHeader_from_thumb(void);

void WriteSaveDataHeader_from_thumb(void)
{
    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(Task_WriteSaveDataHeader_from_thumb);
    data_0217aa0c->taskPending = 1;
}
