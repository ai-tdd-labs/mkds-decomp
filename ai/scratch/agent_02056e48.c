// PURPOSE: Clears the non-ghost save data sections.
//
// Enables the save-data operation, queues its worker task, and marks the
// probably related save-data work object as active.

typedef struct SaveDataWork {
    unsigned char padding_00[0xf8];
    unsigned int active;
} SaveDataWork;

extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void WorkerInsertTask(void (*task)(void));
extern void task_fn_ptr_from_thumb(void);
extern SaveDataWork *data_0217aa0c;

void EraseNonGhostSaveDataSections_from_thumb(void)
{
    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(task_fn_ptr_from_thumb);
    data_0217aa0c->active = 1;
}
