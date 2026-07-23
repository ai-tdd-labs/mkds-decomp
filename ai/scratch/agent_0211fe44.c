// PURPOSE: Saves friend codes and waits for the save system to finish.
// The shared race state gates the friend-code copy and is cleared afterward.
// The save-data holders are probably polled until no pending write remains.
// The first copy destination uses the address of the shared save-data global.

typedef unsigned char u8;

typedef struct RaceState {
    u8 padding_0000[0x1ffc];
    int saveState;
} RaceState;

typedef struct SaveDataHolder {
    u8 padding_00[0x28];
    u8 busy;
} SaveDataHolder;

typedef struct SaveDataIo {
    u8 padding_00[0x0c];
    void *saveData;
    void *saveStorage;
} SaveDataIo;

extern RaceState *data_0217d384;
extern SaveDataHolder *data_0217aa08;
extern SaveDataIo *data_021759d4;

extern void CopyFriendCodesToSaveData(void *destination);
extern void func_02060b68(void);
extern void WriteFriendListSaveDataSection(void);

void WriteSaveFriendCodes(void)
{
    int wait;
    SaveDataHolder *saveHolder;
    SaveDataIo *saveIo;

    if (data_0217d384->saveState == 0) {
        return;
    }

    CopyFriendCodesToSaveData((char *)data_0217d384 + (int)&data_0217aa08);
    func_02060b68();
    WriteFriendListSaveDataSection();

    saveHolder = data_0217aa08;
    saveIo = data_021759d4;
    do {
        if (saveHolder->busy != 0) {
            wait = 1;
        } else {
            wait = (int)saveIo->saveData;
            if (wait != 0) {
                wait = (int)saveIo->saveStorage;
            } else {
                wait = 0;
            }
        }
    } while (wait != 0);

    data_0217d384->saveState = 0;
}
