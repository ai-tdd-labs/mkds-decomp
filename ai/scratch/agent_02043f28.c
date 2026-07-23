// PURPOSE: Reloads the sound banks required by all racers in the current race.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RaceConfig {
    u8 pad_00[0x3d0];
    u8 racerCount;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern u16 data_021540ec[];
extern int MaybeReloadRacerSbnksSwars(int racerId);

void MaybeReloadRacersSfx(int useRacerId)
{
    u32 mask = 0;
    u16 racer = 0;

    if (gRaceConfig->racerCount != 0) {
        do {
            if (useRacerId == 0) {
                mask |= data_021540ec[
                    *(u32 *)((u8 *)gRaceConfig + (u32)racer * 0x30 + 0x250)];
            } else {
                mask |= data_021540ec[
                    *(u32 *)((u8 *)gRaceConfig + (u32)racer * 0x30 + 0x68)];
            }
            racer++;
        } while (racer < gRaceConfig->racerCount);
    }

    MaybeReloadRacerSbnksSwars(mask);
}
