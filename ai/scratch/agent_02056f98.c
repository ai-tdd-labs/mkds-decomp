/* PURPOSE: Starts loading all save data except ghosts.
 * Takes no arguments. It marks the save-data operation as active, clears
 * two status fields, enables save access, and schedules the read task.
 * The exact meanings of the status fields are uncertain.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveDataHolder {
    u8 unknown_00[0x2a];
    u16 status_2a;
    u8 unknown_2c[0x10];
    u8 status_3c;
    u8 unknown_3d[7];
    u32 operationActive : 1;
    u32 unknownFlags : 31;
} SaveDataHolder;

typedef struct SaveWorkerState {
    u8 unknown_00[0xf8];
    u32 taskPending;
} SaveWorkerState;

extern SaveDataHolder *data_0217aa08;
extern SaveWorkerState *data_0217aa0c;

extern void EnableMKDSSVSomeFlag_from_thumb(void);
extern void WorkerInsertTask(void (*task)(void));
extern void Task_ReadNonGhostSaveData_from_thumb(void);

void ReadSaveData_NonGhost_from_thumb(void)
{
    data_0217aa08->operationActive = 1;
    data_0217aa08->status_3c = 0;
    data_0217aa08->status_2a = 0;

    EnableMKDSSVSomeFlag_from_thumb();
    WorkerInsertTask(Task_ReadNonGhostSaveData_from_thumb);

    data_0217aa0c->taskPending = 1;
}
