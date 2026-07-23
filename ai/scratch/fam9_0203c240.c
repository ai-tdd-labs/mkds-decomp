typedef unsigned int u32;

typedef struct {
    unsigned char pad_00[0x40];
    u32 field_40;
    unsigned char pad_44[0x8c - 0x44];
} RacerRecordA;

extern RacerRecordA *data_0217561c;

u32 Maybe_helper_03c240(u32 racerId) {
    return data_0217561c[racerId].field_40;
}
