// PURPOSE: Loads a character's emblem model and animations.
// The context supplies the character index and receives the allocated model,
// joint animation, texture animation, and joint-animation timing values.
// The heap owns those allocations; isPrimary selects the per-character files.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ModelBlock ModelBlock;
typedef struct Animation Animation;
typedef struct JNT0Block JNT0Block;
typedef struct JointAnimation JointAnimation;

typedef struct CharacterKartContext {
    int characterIndex;
    int kartIndex;
    Animation *jointAnimation;
    Animation *textureAnimation;
    ModelBlock *characterModel;
    unsigned char pad_14[0x18];
    int halfLength;
    int frameStep;
} CharacterKartContext;

typedef struct RacerManager {
    unsigned char pad_00[0x28];
    void *faceTextureAnimationData;
} RacerManager;

extern char *FormatCharacterEmblemNsbmdPath(int character, int alt);
extern char *FormatCharacterEmblemNsbtxPath(int character, int flag);
extern char *FormatCharacterEmblemNsbcaPath(int character, int animation);
extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(
    void *heap, void *modelMemory, void *nsbmd, void *nsbtx);
extern void Model_Render(ModelBlock *model, int mode);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int enabled);
extern void Animation_CreateFrom(
    int type, Animation *animation, ModelBlock *model, int count,
    void *heap, void *source);
extern JNT0Block *Anim_NSBCA_LoadGetJNT0Block(void *animationData);
extern JointAnimation *JNT0_LoadJointByIdx(JNT0Block *jointBlock, int index);
extern int GetRacerAnimationIndex(int animation);
extern void Animation_Register(
    Animation *animation, int slot, JointAnimation *joint,
    int animationIndex, void *heap);
extern void Animation_SetAt(Animation *animation, int slot);
extern int Animation_GetCurrentLength(Animation *animation);
extern void Animation_RegisterAll(
    Animation *animation, void *animationData, void *heap);
extern int _s32_div_f(int numerator, int denominator);
extern int FX_Div(int numerator, int denominator);

extern RacerManager *data_0217ad00;

void StructAD00Sub_LoadCharacterEmblem_from_thumb(
    CharacterKartContext *context, void *heap, int isPrimary)
{
    u16 character;
    int hasIdleAnimation;
    void *nsbmd;
    void *nsbtx;
    ModelBlock *model;
    u16 animation;

    character = (u16)context->characterIndex;
    nsbmd = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
        FormatCharacterEmblemNsbmdPath(character, isPrimary));
    nsbtx = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(
        FormatCharacterEmblemNsbtxPath(character, isPrimary));

    context->characterModel = Mem_AllocateHeap(heap, 0x6c);
    model = Model_CreateFromNsbmdNsbtxMetaCopy(
        heap, context->characterModel, nsbmd, nsbtx);
    Model_Render(context->characterModel, 3);
    ModelBlock_SomeMatFn(model, 0);

    if (isPrimary != 0) {
        animation = 0;
        hasIdleAnimation = 0;
        context->jointAnimation = Mem_AllocateHeap(heap, 0x38);
        Animation_CreateFrom(
            0, context->jointAnimation, context->characterModel, 4, heap, 0);

        do {
            void *animationData;

            animationData = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
                FormatCharacterEmblemNsbcaPath(character, animation));
            if (animationData != 0) {
                JointAnimation *joint;

                joint = JNT0_LoadJointByIdx(
                    Anim_NSBCA_LoadGetJNT0Block(animationData), 0);
                Animation_Register(
                    context->jointAnimation, animation, joint,
                    GetRacerAnimationIndex(animation), heap);
                if (animation == 0) {
                    hasIdleAnimation = 1;
                }
            }
            animation++;
        } while (animation < 4);

        if (hasIdleAnimation != 0) {
            Animation_SetAt(context->jointAnimation, 0);
            context->halfLength = _s32_div_f(
                Animation_GetCurrentLength(context->jointAnimation) - 0x1000,
                2);
            context->frameStep = FX_Div(0x1000, context->halfLength);
        } else {
            *(u16 *)((unsigned char *)context->jointAnimation + 0x18) = 0;
        }
    }

    context->textureAnimation = Mem_AllocateHeap(heap, 0x38);
    Animation_CreateFrom(
        2, context->textureAnimation, context->characterModel, 1, heap, 0);
    Animation_RegisterAll(
        context->textureAnimation,
        data_0217ad00->faceTextureAnimationData,
        heap);
    Animation_SetAt(context->textureAnimation, 0);
}
