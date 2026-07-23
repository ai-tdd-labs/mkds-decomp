typedef unsigned int u32;

typedef struct {
    unsigned char raw[0x30];
} RacerSlotB;

typedef struct {
    unsigned char pad_00[0x78];
    u32 field_78;
} RacerRecordB;

extern RacerSlotB *gRaceConfig;

u32 Maybe_helper_0cc6a4(u32 racerId) {
    return ((RacerRecordB *)&gRaceConfig[racerId])->field_78;
}
