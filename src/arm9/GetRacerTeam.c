typedef unsigned int u32;

typedef struct {
    unsigned char raw[0x30];
} RacerSlotB;

typedef struct {
    unsigned char pad_00[0x74];
    u32 field_74;
} RacerRecordB;

extern RacerSlotB *gRaceConfig;

u32 GetRacerTeam(u32 racerId) {
    return ((RacerRecordB *)&gRaceConfig[racerId])->field_74;
}
