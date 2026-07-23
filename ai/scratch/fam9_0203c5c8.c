typedef unsigned int u32;

typedef struct {
    unsigned char pad_00[0x58];
    u32 field_58;
    unsigned char pad_5c[0x8c - 0x5c];
} RacerRecordA;

extern RacerRecordA *data_0217561c;

u32 GetSomeRacerValue(u32 racerId) {
    return data_0217561c[racerId].field_58;
}
