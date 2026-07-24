// PURPOSE: Computes and stores the skill rank points for one driver.
// racer selects the driver whose race result is scored.
// Grand Prix and battle races use different score components.
// The returned total is limited to the signed rank-point range.

typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

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

typedef struct DriverStatus {
    char pad_000[0x30];
    u16 flags;
    char pad_032[0x8c - 0x32];
} DriverStatus;

typedef struct RaceStatus {
    u32 time_frame_counter;
    char pad_004[0x14 - 0x04];
    DriverStatus drivers[8];
    char pad_474[0x500 - 0x474];
    SkillRankpoints skill_rankpoints;
} RaceStatus;

typedef struct BattleRankFactors {
    u16 unknown_00;
    u16 target_time;
    s16 time_factor;
} BattleRankFactors;

typedef struct RaceConfig {
    char pad_000[0x08];
    s32 mode;
    char pad_00c[0x28 - 0x0c];
    BattleRankFactors battle_rank_factors;
} RaceConfig;

typedef struct StructRK {
    u32 start_boost;
    u32 drift_count;
    u32 item_hit_count;
    u32 offroad_time_count;
    u32 wall_hit_count;
    u32 damage_count;
    u32 respawn_count;
} StructRK;

extern RaceStatus *data_0217561c;
extern RaceConfig *gRaceConfig;

extern void MaybeComputeGPScore(SkillRankpoints *score, s32 racer);
extern StructRK *GetGlobalRK(void);
extern void FX_Div(void *a0);

s16 ComputeDriverSkillRankpoints(s32 racer)
{
    SkillRankpoints score;
    RaceStatus *race = data_0217561c;
    SkillRankpoints *stored_score = &race->skill_rankpoints;
    s32 total;

    if ((race->drivers[racer].flags & 1) == 0) {
        return 0;
    }

    switch (gRaceConfig->mode) {
    case 0:
        MaybeComputeGPScore(&score, racer);
        break;

    case 4:
    {
        BattleRankFactors *factors = &gRaceConfig->battle_rank_factors;
        StructRK *rk = GetGlobalRK();

        score.rank_time_delta_points =
            ((s32 (*)(s32, s32))FX_Div)(
                ((factors->target_time - race->time_frame_counter) *
                 factors->time_factor)
                    << 12,
                1000 << 12) >>
            12;
        score.first_place_percentage_points = 0;
        score.start_boost_points = 0;
        score.drift_points = 0;
        score.item_hit_points = rk->item_hit_count * -5;
        score.offroad_time_points = 0;
        score.wall_hit_points = rk->wall_hit_count * -5;
        score.damage_points = rk->damage_count * -10;
        score.respawn_points = rk->respawn_count * -20;
        break;
    }

    default:
        return 0;
    }

    *stored_score = score;
    total = stored_score->rank_time_delta_points +
            stored_score->first_place_percentage_points +
            stored_score->start_boost_points +
            stored_score->drift_points +
            stored_score->item_hit_points +
            stored_score->offroad_time_points +
            stored_score->wall_hit_points +
            stored_score->damage_points +
            stored_score->respawn_points;

    if (total < -9999) {
        total = -9999;
    }
    if (total > 9999) {
        total = 9999;
    }

    return total;
}
