/* PURPOSE: Creates the resources used by the kart selection menu.
 * The heap argument owns the menu parameter files, model resources, and two
 * per-player CE entries created here. It also probably connects the current
 * player profile's custom emblem data when that feature is available.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ExecutionState {
    u8 pad_00[0x1c];
    u32 flags;
} ExecutionState;

typedef struct CEEntry {
    u8 raw[0x34];
} CEEntry;

typedef struct GlobalCE {
    u8 pad_000[0x18];
    void *characterMenuParams;
    void *kartMenuParams;
    u8 pad_020[0x1c8];
    void *customEmblemData;
    void *customEmblemPalette;
    u8 pad_1f0[4];
    CEEntry entries[2];
} GlobalCE;

typedef struct SystemProfileData {
    u8 pad_00[0x31];
    u8 unusedFlags : 3;
    u8 customEmblemBlocked : 1;
    u8 remainingFlags : 4;
} SystemProfileData;

typedef struct PlayerProfileData {
    u8 pad_00[4];
    u8 hasCustomEmblem : 1;
    u8 remainingFlags : 7;
} PlayerProfileData;

typedef struct SaveDataRoot {
    SystemProfileData *systemProfile;
    PlayerProfileData *playerProfile;
} SaveDataRoot;

typedef struct EmblemPalette {
    u8 pad_00[0xc];
    void *colors;
} EmblemPalette;

extern ExecutionState *data_021759d0;
extern SaveDataRoot *data_0217aa08;
extern GlobalCE *data_0217ad08;
extern char data_02165738[];
extern char data_0216574c[];

extern void SetActiveExecutionContextHeapGroupId_from_thumb(int groupId);
extern void func_02062860(void);
extern void func_02012b20(int value);
extern void func_02077bc0(void *heap);
extern void InitializeModelResourceList(void);
extern void SetCurrentlyInKartModelMenu(int enabled);
extern void InitializeGlobalCE_from_thumb(void *heap);
extern void LoadKartAppearTablePointerCE_from_thumb(void *heap, int tableIndex);
extern void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst);
extern void CreateCEML_from_thumb(void *heap);
extern void CreateCESex_from_thumb(void *heap, CEEntry *entry);
extern EmblemPalette *GetEmblemPalette_from_thumb(void);

void CreateGlobalCE_from_thumb(void *heap)
{
    u16 i;

    SetActiveExecutionContextHeapGroupId_from_thumb(1);
    func_02062860();
    func_02012b20(0);

    data_021759d0->flags &= ~8u;
    func_02077bc0(heap);
    InitializeModelResourceList();
    SetCurrentlyInKartModelMenu(1);

    InitializeGlobalCE_from_thumb(heap);
    LoadKartAppearTablePointerCE_from_thumb(heap, 0);
    ReadKartModelMenuFile_from_thumb(
        heap, data_02165738, &data_0217ad08->characterMenuParams);
    ReadKartModelMenuFile_from_thumb(
        heap, data_0216574c, &data_0217ad08->kartMenuParams);
    CreateCEML_from_thumb(heap);

    for (i = 0; i < 2; i++) {
        CreateCESex_from_thumb(heap, &data_0217ad08->entries[i]);
    }

    {
        SaveDataRoot *saveData = data_0217aa08;
        PlayerProfileData *playerProfile = saveData->playerProfile;

        if (playerProfile->hasCustomEmblem &&
            !saveData->systemProfile->customEmblemBlocked) {
            /* The usable emblem bytes begin eight bytes into the profile block. */
            data_0217ad08->customEmblemData = (u8 *)playerProfile + 8;
            data_0217ad08->customEmblemPalette =
                GetEmblemPalette_from_thumb()->colors;
        }
    }

    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
