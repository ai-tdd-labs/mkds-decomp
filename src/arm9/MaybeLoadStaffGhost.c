// PURPOSE: Loads the staff ghost for a selected racer.
// The first argument is unused, while racerIndex selects the racer slot.
// Missing or invalid ghost data restores the normal default racer setup.
// Valid data supplies the recorded kart, character, replay, and race times.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StaffGhostRecord {
    u8 pad_000[4];
    unsigned int kart : 4;
    unsigned int character : 6;
    unsigned int settings_pad : 22;
    unsigned int valid : 1;
    unsigned int status_pad : 31;
    u8 pad_00c[0x230 - 0x00c];
    u8 replay[1];
} StaffGhostRecord;

typedef struct SaveDataRoot {
    u8 pad_000[0x1c];
    StaffGhostRecord *staff_ghost;
} SaveDataRoot;

typedef struct RaceConfig {
    u8 pad_000[0x1f4];
    int mode;
    u8 pad_1f8[0x3e8 - 0x1f8];
    u32 main_time;
    u32 split_times[5];
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern SaveDataRoot *data_0217aa08;
extern u8 data_02175650[];

extern void StructCO_ConfigureRacerDefault(void *racer, int kart,
                                           int character, int mode,
                                           int player, int count);
extern void Mem_CpuCopy8(const volatile void *source,
                         volatile void *destination, u32 size);
extern void StructNKPG_CopyToTime_from_thumb(void *ghost, void *time);
extern void StructNKPG_AnotherCopyToTime_from_thumb(void *ghost, int index,
                                                    void *time);

int MaybeLoadStaffGhost(void *unused, int racerIndex)
{
    StaffGhostRecord *ghost;
    u8 splitIndex;

    if (gRaceConfig->mode == 2) {
        return 1;
    }

    ghost = data_0217aa08->staff_ghost;
    if (ghost == 0) {
        goto use_default;
    }
    if (ghost->valid != 1) {
        goto use_default;
    }

    StructCO_ConfigureRacerDefault((void *)racerIndex, ghost->kart,
                                   ghost->character, 2, -1, 3);

    *(int *)((u8 *)gRaceConfig + racerIndex * 0x30 + 0x268) = 2;
    Mem_CpuCopy8(ghost->replay,
                 *(void **)(data_02175650 + racerIndex * 0x5c), 0xdcc);

    StructNKPG_CopyToTime_from_thumb(ghost, &gRaceConfig->main_time);

    for (splitIndex = 1; splitIndex <= 5; splitIndex++) {
        StructNKPG_AnotherCopyToTime_from_thumb(
            ghost, splitIndex, &gRaceConfig->split_times[splitIndex - 1]);
    }

    return 1;

use_default:
    StructCO_ConfigureRacerDefault((void *)racerIndex, 0, 0, 4, -1, 3);
    return 0;
}
