// PURPOSE: Updates a racer's character animation blend and completes queued transitions.
// The racer provides movement flags and a character-animation context.
// The blend offset moves toward either limit or returns to zero.
// A completed primary animation probably starts the queued animation.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AnimationTrack {
    int value;
} AnimationTrack;

typedef struct Animation {
    u8 unknown_00[2];
    u16 state;
    u8 unknown_04[8];
    int progress;
    u8 unknown_10[0x0a];
    u16 animation_index;
    AnimationTrack **tracks;
} Animation;

typedef struct AnimationState {
    int offset;
    u8 unknown_04[4];
    int limit;
    u8 unknown_0c[8];
    int active;
    u16 next_animation;
} AnimationState;

typedef struct CharacterKartContext {
    u8 unknown_00[8];
    Animation *animation;
    Animation *secondary_animation;
    u8 unknown_10[0x14];
    AnimationState animation_state;
} CharacterKartContext;

typedef struct StructMQRacerEntry {
    u8 unknown_000[0x44];
    u32 field_044;
    u32 field_048;
    u8 unknown_04c[0x590 - 0x4c];
    CharacterKartContext *character_context;
} StructMQRacerEntry;

typedef struct RaceConfig {
    u8 unknown_00[0x0c];
    int scene_id;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern int data_021551a4;

extern void Animation_Update(Animation *animation);
extern void Animation_SetLoop(Animation *animation, int animation_index,
                              int loop);
extern void Animation_SetWithBlendAt(Animation *animation, u16 animation_index);
extern void Animation_UpdateBlend(Animation *animation);

void StructMQRacerEntry_SomeFn_20(StructMQRacerEntry *entry)
{
    CharacterKartContext *context = entry->character_context;
    AnimationState *state = &context->animation_state;
    Animation *animation = context->animation;
    int step = (entry->field_044 & 8) ? 0x2000 : 0x1000;
    u32 flags = entry->field_048;
    int limit = state->limit;

    if ((flags & 8) != 0) {
        if (gRaceConfig->scene_id != 6) {
            state->offset += step;
            if (state->offset > limit) {
                state->offset = limit;
            }
        }
    } else if ((flags & 0x10) != 0) {
        if (gRaceConfig->scene_id != 6) {
            state->offset -= step;
            if (state->offset < -limit) {
                state->offset = -limit;
            }
        }
    } else if (state->offset != 0) {
        if (state->offset > 0) {
            state->offset -= step;
            if (state->offset < 0) {
                state->offset = 0;
            }
        } else {
            state->offset += step;
            if (state->offset > 0) {
                state->offset = 0;
            }
        }
    }

    if (animation->animation_index != 0) {
        Animation *secondary;

        Animation_Update(animation);
        if (state->active == 0) {
            return;
        }
        if (animation->state != 1) {
            return;
        }

        Animation_SetLoop(animation, animation->animation_index, 1);
        Animation_SetWithBlendAt(context->animation, state->next_animation);

        secondary = context->secondary_animation;
        secondary->progress = data_021551a4;
        secondary->tracks[secondary->animation_index]->value =
            secondary->progress;
        state->active = 0;
    } else {
        animation->progress = state->offset + state->limit;
        Animation_UpdateBlend(animation);
    }
}
