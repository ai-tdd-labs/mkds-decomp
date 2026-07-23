// PURPOSE: Starts a racer animation and records its blend setting.
// The racer supplies a character-animation context and an animation number.
// The context probably remembers whether an earlier animation needs looping.
// The final argument is stored as the animation's blend setting.

typedef unsigned short u16;

typedef struct Animation {
    unsigned char unknown_00[0x1a];
    u16 loop_index;
} Animation;

typedef struct AnimationState {
    unsigned char unknown_00[0x14];
    int active;
    u16 blend;
} AnimationState;

typedef struct CharacterKartContext {
    unsigned char unknown_00[8];
    Animation *animation;
    unsigned char unknown_0c[0x18];
    AnimationState state;
} CharacterKartContext;

typedef struct StructMQRacerEntry {
    unsigned char unknown_000[0x590];
    CharacterKartContext *character_context;
} StructMQRacerEntry;

extern void Animation_SetLoop(Animation *animation, int animation_index,
                              int loop);
extern void Animation_SetWithBlendAt(Animation *animation, u16 animation_index);

void StructMQRacerEntry_SomeFn_7(StructMQRacerEntry *entry, int animation_index,
                                 u16 blend)
{
    CharacterKartContext *context = entry->character_context;
    Animation *animation = context->animation;
    AnimationState *state = (AnimationState *)((unsigned char *)context + 0x24);

    if (state->active != 0) {
        if (animation->loop_index != 0) {
            Animation_SetLoop(animation, animation->loop_index, 1);
        }
    }

    state->active = 1;
    state->blend = blend;
    Animation_SetWithBlendAt(entry->character_context->animation,
                             animation_index);
    Animation_SetLoop(animation, (u16)animation_index, 0);
}
