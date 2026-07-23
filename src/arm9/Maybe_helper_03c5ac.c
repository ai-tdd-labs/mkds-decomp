typedef unsigned int u32;

typedef struct {
    unsigned char pad_00[0x5c];
    u32 field_5c;
    unsigned char pad_60[0x8c - 0x60];
} RacerRecordA;

extern RacerRecordA *data_0217561c;

u32 Maybe_helper_03c5ac(u32 racerId) {
    return data_0217561c[racerId].field_5c;
}
