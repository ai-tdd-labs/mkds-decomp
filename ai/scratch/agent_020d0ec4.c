// PURPOSE: Reports whether the cup selection worker has no pending task.
// Checks that the cup-selection work object exists, then asks its worker
// whether a task is pending.

#pragma optimize_for_size on

typedef struct CupPictureWork CupPictureWork;

#define data_0217b4a4 (*(CupPictureWork **)0x0217b4a4)
extern int WorkerHasPendingTask(CupPictureWork *work);

int func_020d0ec4(void)
{
    if (data_0217b4a4 == 0) {
        goto no_task;
    }
    if (WorkerHasPendingTask(data_0217b4a4) != 0) {
        goto no_task;
    }
    return 1;

no_task:
    return 0;
}
