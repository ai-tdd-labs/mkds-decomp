// PURPOSE: Computes the Grand Prix score components for one racer.
// score receives nine components based on race timing and driving statistics.
// racer selects the current driver's race-status entry.
// The scaling factors probably come from the loaded ranktimeGP.rtt data.

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct DriverStatus {
    char pad_00[0x28];
    u32 first_place_time;
    char pad_2c[0x8c - 0x2c];
} DriverStatus;

typedef struct RanktimeGp {
    char pad_00[0x0a];
    u16 delta_factor;
    u16 first_place_percentage_factor;
    u16 start_boost_factor;
    u16 drift_factor;
    u16 item_hit_factor;
    u16 offroad_time_factor;
    u16 wall_hit_factor;
    u16 damage_factor;
    u16 respawn_factor;
} RanktimeGp;

typedef struct RaceStatus {
    u32 time_frame_counter;
    char pad_004[8];
    u16 ranktime_gp_val;
    char pad_00e[6];
    DriverStatus drivers[8];
    char pad_474[0x54];
    RanktimeGp *ranktime_gp;
} RaceStatus;

typedef struct StructRK {
    u32 start_boost;
    u32 drift_count;
    u32 item_hit_count;
    u32 offroad_time_count;
    u32 wall_hit_count;
    u32 damage_count;
    u32 respawn_count;
} StructRK;

typedef struct SkillRankpoints {
    s32 rank_time_delta_points;
    s32 first_place_percentage_points;
    s32 start_boost_points;
    s32 drift_points;
    s32 item_hit_points;
    s32 offroad_time_points;
    s32 wall_hit_points;
    s32 damage_points;
    s32 respawn_points;
} SkillRankpoints;

extern StructRK *GetGlobalRK(void);
extern void FX_Div(void *a0);
extern void FX_Inv(void *a0);
extern RaceStatus *data_0217561c;

void MaybeComputeGPScore(SkillRankpoints *score, s32 racer)
{
    StructRK *rk = GetGlobalRK();
    RaceStatus *race = data_0217561c;
    DriverStatus *driver = &race->drivers[racer];
    RanktimeGp *factors = race->ranktime_gp;

    if (race->ranktime_gp_val == 0) {
        score->rank_time_delta_points = 0;
    } else {
        score->rank_time_delta_points =
            (((s32 (*)(s32, s32))FX_Div)(
                 (race->ranktime_gp_val - race->time_frame_counter) *
                     factors->delta_factor,
                 race->ranktime_gp_val) +
             0x800) >>
            12;
    }

    score->first_place_percentage_points =
        (((s32 (*)(s32, s32))FX_Div)(
             driver->first_place_time << 12,
             data_0217561c->ranktime_gp_val << 12) *
         factors->first_place_percentage_factor) >>
        12;

    if (rk->start_boost != 0) {
        score->start_boost_points = factors->start_boost_factor;
    } else {
        score->start_boost_points = 0;
    }

    score->drift_points = factors->drift_factor * rk->drift_count;
    score->item_hit_points = factors->item_hit_factor * rk->item_hit_count;
    score->offroad_time_points =
        -(s32)((rk->offroad_time_count *
                ((u32 (*)(u32))FX_Inv)(factors->offroad_time_factor << 12)) >>
               12);
    score->wall_hit_points = -factors->wall_hit_factor * rk->wall_hit_count;
    score->damage_points = -factors->damage_factor * rk->damage_count;
    score->respawn_points = -factors->respawn_factor * rk->respawn_count;
}
