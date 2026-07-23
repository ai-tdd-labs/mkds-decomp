// PURPOSE: Loads save data and clears its first-load flag.
// This handler has no arguments.
// It starts the non-ghost save-data load, then probably marks that initial load complete.

typedef struct SaveDataState {
    char pad_00[0x2c];
    int flags;
} SaveDataState;

#define data_021a99e0 (*(SaveDataState **)0x021a99e0)
extern void ReadSaveData_NonGhost_from_thumb(void);

void Logo_StateHandler_ReadSaveData_First(void) {
    ReadSaveData_NonGhost_from_thumb();
    data_021a99e0->flags &= ~2; // Clear the first-load state bit.
}
