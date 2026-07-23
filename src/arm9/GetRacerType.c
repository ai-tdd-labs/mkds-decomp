typedef unsigned int u32;

typedef struct {
    unsigned char raw[0x30];
} RacerSlotB;

typedef struct {
    unsigned char pad_00[0x70];
    u32 field_70;
} RacerRecordB;

extern RacerSlotB *gRaceConfig;

u32 GetRacerType(u32 racerId) {
    return ((RacerRecordB *)&gRaceConfig[racerId])->field_70;
}
