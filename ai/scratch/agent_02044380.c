// PURPOSE: Applies a race setup and initializes all racer slots.
// The setup supplies shared settings and the kart and character for two racers.
// The other arguments are saved as additional setup bytes.
// Missing second-racer values probably select the normal default racer.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RaceSetup {
    u8 pad_00[8];
    u8 field_08;
    u8 field_09;
    u8 racer0_kart;
    u8 racer0_character;
    u8 pad_0c[0x10];
    u16 flags;
    u8 racer1_kart;
    u8 racer1_character;
    u8 pad_20[0xc];
} RaceSetup;

typedef struct RaceConfig {
    u8 pad_000[0x1e8];
    u32 field_1e8;
    u8 pad_1ec[4];
    u32 field_1f0;
    u8 pad_1f4[4];
    u32 field_1f8;
    u32 field_1fc;
    u32 field_200;
    u32 field_204;
    u32 field_208;
    u8 pad_20c[4];
    RaceSetup setup;
    u8 field_23c;
    u8 field_23d;
    u8 pad_23e;
    u8 field_23f;
    u8 field_240;
    u8 pad_241[0x197];
    u16 field_3d8;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern void StructCO_ConfigureRacerDefault(void *racer, int kart,
                                           int character, int mode,
                                           int player, int count);

void func_02044380(const RaceSetup *setup, u8 field_23c, u8 field_23d)
{
    u8 racer;

    gRaceConfig->setup = *setup;
    gRaceConfig->field_23c = field_23c;
    gRaceConfig->field_23d = field_23d;
    gRaceConfig->field_1f0 = 4;
    gRaceConfig->field_1e8 = setup->field_08;
    gRaceConfig->field_23f = (setup->flags & 0x10) != 0;
    gRaceConfig->field_240 = 0;
    gRaceConfig->field_204 = 0;
    gRaceConfig->field_208 = 0;
    gRaceConfig->field_200 = 0;
    gRaceConfig->field_3d8 = 0;
    gRaceConfig->field_1f8 = setup->field_09;

    StructCO_ConfigureRacerDefault(0, setup->racer0_kart,
                                   setup->racer0_character, 0, -1, 3);

    if (setup->racer1_kart != 0xff &&
        setup->racer1_character != 0xff) {
        StructCO_ConfigureRacerDefault((void *)1, setup->racer1_kart,
                                       setup->racer1_character, 1, -1, 3);
        gRaceConfig->field_1fc = 2;
    } else {
        StructCO_ConfigureRacerDefault((void *)1, -1, -1, 4, -1, 3);
        gRaceConfig->field_1fc = 0;
    }

    for (racer = 2; racer < 8; racer++) {
        StructCO_ConfigureRacerDefault((void *)(u32)racer,
                                       -1, -1, 4, -1, 3);
    }
}
