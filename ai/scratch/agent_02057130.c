/* PURPOSE: Replaces an empty save file with fresh save data.
 * The shared system mode probably decides whether the user name is preserved.
 * Outside mode 2, this queues the non-ghost save writer and marks its worker
 * task as pending.
 */

typedef struct WorkerContext {
    unsigned char reserved[0xf8];
    unsigned int taskPending;
} WorkerContext;

extern WorkerContext *data_0217aa0c;

extern void ClearAllSaveDataSections_from_thumb(int preserveUserName);
extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void Task_WriteNonGhostSaveData_from_thumb(void);
extern int WorkerInsertTask(void (*task)(void));

void OverwriteEmptySaveData_from_thumb(void)
{
    ClearAllSaveDataSections_from_thumb(
        *(volatile unsigned short *)0x027ffc40 == 2);

    if (*(volatile unsigned short *)0x027ffc40 != 2) {
        EnableMKDSSVSomeFlag_from_thumb();
        WorkerInsertTask(Task_WriteNonGhostSaveData_from_thumb);
        data_0217aa0c->taskPending = 1;
    }
}
