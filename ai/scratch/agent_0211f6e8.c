// PURPOSE: Saves the current friend-list state and waits for save work to finish.
// The two arguments are probably friend-list slot identifiers, passed in reverse order.
// It updates the shared friend data, refreshes the friend list, and waits until all
// related save-data activity reports idle.

#pragma optimize_for_size on

typedef unsigned char u8;

typedef struct RaceSaveState {
    u8 pad_00[0x19f0];
} RaceSaveState;

typedef struct SaveActivityState {
    u8 pad_00[0x28];
    u8 busy;
} SaveActivityState;

typedef struct SaveIoState {
    u8 pad_00[0x0c];
    int field_0c;
    int field_10;
} SaveIoState;

extern RaceSaveState *data_0217d384;
extern SaveActivityState *data_0217aa08;
extern SaveIoState *data_021759d4;

extern void OI_JoinInSlot1FreeSlot2(int slot1, int slot2);
extern void CopyFriendCodesToSaveData(void *destination);
extern void func_02060b68(void);
extern void *WriteFriendListSaveDataSection(void);

void func_0211f6e8(int slot1, int slot2)
{
    int status;

    OI_JoinInSlot1FreeSlot2((u8)slot2, (u8)slot1);
    CopyFriendCodesToSaveData((u8 *)data_0217d384 + 0x19f0);
    func_02060b68();
    WriteFriendListSaveDataSection();

    do {
        status = data_0217aa08->busy != 0
            ? 1
            : (data_021759d4->field_0c != 0
                ? data_021759d4->field_10
                : 0);
    } while (status != 0);
}
