// PURPOSE: Configures a driver's kart and character physics.
// The driver context selects the physical-parameter records to use.
// Award scenes retain the default values; two race modes reduce speed and drift.
// Character physics scale collision-speed values that are below their normal limit.

typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct KartPhysicalParam {
    s32 collision_sphere_size;
    unsigned char pad_004[0x0c];
    s32 max_speed;
    unsigned char pad_014[0x1e];
    s16 drift;
    unsigned char pad_034[0x34];
    s32 collision_speed_multipliers[12];
} KartPhysicalParam;

typedef struct CharacterPhysicalParam {
    s32 collision_speed_multiplier;
} CharacterPhysicalParam;

typedef struct DriverContext {
    unsigned char pad_000[0x74];
    u16 driver_id;
    unsigned char pad_076[0x256];
    KartPhysicalParam *kart_phys_param;
    CharacterPhysicalParam *char_phys_param;
    unsigned char pad_2d4[0x120];
    s32 collision_speed_divisor;
} DriverContext;

typedef struct RaceConfig {
    unsigned char pad_000[0x10];
    s32 race_mode;
} RaceConfig;

extern KartPhysicalParam *GetKartPhysicalParam(int driver_id);
extern CharacterPhysicalParam *GetCharacterPhysicalParam(int driver_id);
extern int IsAwardOrStaffRoll_0(void);
extern void FX_Div(void *a0);
extern RaceConfig *gRaceConfig;

void DriverContext_PrepareCharacterKartPhysicalParams(DriverContext *driver)
{
    s32 speed_scale;
    s32 drift_adjustment;
    s16 i;

    driver->kart_phys_param = GetKartPhysicalParam(driver->driver_id);

    speed_scale = 0x1000;
    drift_adjustment = 0;
    if (IsAwardOrStaffRoll_0() == 0) {
        switch (gRaceConfig->race_mode) {
        case 0:
            speed_scale = 0xb33;
            drift_adjustment = -0x28;
            break;
        case 1:
            speed_scale = 0xd9a;
            drift_adjustment = -0x14;
            break;
        }
    }

    driver->kart_phys_param->max_speed =
        (s32)(((long long)driver->kart_phys_param->max_speed * speed_scale) >> 12);
    driver->kart_phys_param->drift += drift_adjustment;

    driver->collision_speed_divisor =
        0x1000 - driver->kart_phys_param->collision_speed_multipliers[4];
    driver->collision_speed_divisor =
        ((s32 (*)(s32, s32))FX_Div)(
            driver->collision_speed_divisor,
            driver->kart_phys_param->collision_sphere_size << 1);

    driver->char_phys_param = GetCharacterPhysicalParam(driver->driver_id);

    for (i = 0; i < 12; i++) {
        if (driver->kart_phys_param->collision_speed_multipliers[i] < 0x1000) {
            driver->kart_phys_param->collision_speed_multipliers[i] =
                (s32)(((long long)
                           driver->kart_phys_param->collision_speed_multipliers[i] *
                       driver->char_phys_param->collision_speed_multiplier +
                       0x800) >>
                      12);
        }
    }
}
