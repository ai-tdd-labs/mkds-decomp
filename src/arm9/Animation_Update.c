// PURPOSE: Updates an animation and finishes a completed blend.
// The animation probably owns the active track, its track table, and an optional
// previous track used while blending.  A completed blend is committed before the
// regular animation update runs.

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
extern void Animation_UpdateImpl(Animation *animation);

void Animation_Update(Animation *animation)
{
    if (animation->blend_state != 0) {
        animation->tracks[animation->active_track]->weight += animation->blend_amount;
        animation->previous_track->weight -= animation->blend_amount;

        if (animation->tracks[animation->active_track]->weight >= 0x1000) {
            animation->blend_state = 0;
            animation->tracks[animation->active_track]->weight = 0x1000;
            StructML_SomeFn_2(animation->field_14, animation->previous_track);
            animation->previous_track = 0;
        }
    }

    Animation_UpdateImpl(animation);
    animation->tracks[animation->active_track]->field_00 = *(int *)((char *)animation + 0xc);
}
