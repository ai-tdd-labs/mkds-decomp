// PURPOSE: Sets a kart character animation at a chosen frame.
// The context probably stores its animation controller at offset 0x08.
// The flag selects whether the animation changes with blending.

typedef unsigned short u16;

typedef struct CharacterKartContext {
    char padding[8];
    void *animation;
} CharacterKartContext;

extern void Animation_SetWithBlendAt(void *animation, int animation_index,
                                     int blend);
extern void Animation_SetAt(void *animation, int animation_index);

void CharacterKartContext_SetNsbcaAnimAt(CharacterKartContext *context,
                                         int animation_index, int blend)
{
    if (blend != 0) {
        Animation_SetWithBlendAt(context->animation, (u16)animation_index,
                                 blend);
    } else {
        Animation_SetAt(context->animation, (u16)animation_index);
    }
}
