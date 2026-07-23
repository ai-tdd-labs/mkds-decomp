typedef unsigned int u32;

typedef struct {
    unsigned char raw[0x30];
} RacerSlotB;

typedef struct {
    unsigned char pad_00[0x6c];
    u32 field_6c;
} RacerRecordB;

extern RacerSlotB *gRaceConfig;

u32 GetRacerKartId(u32 racerId) {
    return ((RacerRecordB *)&gRaceConfig[racerId])->field_6c;
}
