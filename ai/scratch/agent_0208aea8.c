// PURPOSE: Copies physical parameters from a selected kart and character.
// Arguments: destination slot, character slot, and kart slot.
// Award and staff-roll scenes probably force both source slots to zero.
// The function copies a 0x98-byte parameter record and then its 8-byte pair.

typedef unsigned int u32;
typedef struct KartParamFile KartParamFile;

typedef struct PhysicalParamState {
    void *kartParams;
    void *pairBuf;
    void *kartTable;
    KartParamFile *kartFile;
    void *charFile;
} PhysicalParamState;

typedef struct RaceConfig {
    int field0;
    int field4;
    int raceMode;
} RaceConfig;

extern PhysicalParamState *gPhysicalParams;
extern RaceConfig *gRaceConfig;
extern int IsAwardOrStaffRoll_0(void);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void CopyKartCharPhysicalParam(int destination, int character, int kart)
{
    KartParamFile *kartFile = gPhysicalParams->kartFile;
    void *charFile = gPhysicalParams->charFile;

    if (IsAwardOrStaffRoll_0()) {
        kart = 0;
        character = kart;
    } else if (gRaceConfig->raceMode == 2) {
        character = (unsigned short)(kart + 0x25);
    }

    Mem_CpuCopy8((char *)kartFile + character * 0x98,
                 (char *)gPhysicalParams->kartParams + destination * 0x98,
                 0x98);
    Mem_CpuCopy8((char *)charFile + kart * 8,
                 (char *)gPhysicalParams->pairBuf + destination * 8,
                 8);
}
