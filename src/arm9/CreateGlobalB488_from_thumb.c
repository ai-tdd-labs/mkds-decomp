// PURPOSE: Initializes the shared cup progress state.
// Clears the full state block and resets the fields used by cup progression.
// The state layout is only partially known, so unnamed bytes preserve offsets.

typedef struct CupProgressState {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
    unsigned char padding_18[4];
    int f1c;
    unsigned char padding_20[0x34];
    unsigned char f54;
    unsigned char padding_55[3];
    int f58;
    unsigned char padding_5c[0x14];
    int f70;
} CupProgressState;

extern void SpecialMemoryZero_0(void *dst, unsigned int size);
extern CupProgressState *data_0217b488;

void CreateGlobalB488_from_thumb(void) {
    SpecialMemoryZero_0(data_0217b488, 0x130);

    data_0217b488->f00 = 0;
    data_0217b488->f04 = 0;
    data_0217b488->f08 = 0;
    data_0217b488->f0c = 0;
    data_0217b488->f10 = 0;
    data_0217b488->f14 = 0;
    data_0217b488->f1c = 0;
    data_0217b488->f54 = 0;
    data_0217b488->f58 = 0;
    data_0217b488->f70 = 0;
}
