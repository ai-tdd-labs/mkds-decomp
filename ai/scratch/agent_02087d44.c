// PURPOSE: Updates the blend between two animation tracks.
// The animation probably keeps the active track index, a track table, and a
// blend amount in this structure.  Once the active track reaches full weight,
// it clears the blend state and updates the previous track.

typedef unsigned short u16;

typedef struct AnimationTrack {
    int field_00;
    int weight;
} AnimationTrack;

typedef struct Animation {
    char pad_00[0x14];
    void *field_14;
    char pad_18[2];
    u16 active_track;
    AnimationTrack **tracks;
    char pad_20[0x2c - 0x20];
    void *blend_state;
    int blend_amount;
    AnimationTrack *previous_track;
} Animation;

extern void StructML_SomeFn_2(void *arg0, AnimationTrack *arg1);

void Animation_UpdateBlend(Animation *animation)
{
    if (animation->blend_state == 0) {
        return;
    }

    animation->tracks[animation->active_track]->weight += animation->blend_amount;
    animation->previous_track->weight -= animation->blend_amount;

    if (animation->tracks[animation->active_track]->weight < 0x1000) {
        return;
    }

    animation->blend_state = 0;
    animation->tracks[animation->active_track]->weight = 0x1000;
    StructML_SomeFn_2(animation->field_14, animation->previous_track);
    animation->previous_track = 0;
}
