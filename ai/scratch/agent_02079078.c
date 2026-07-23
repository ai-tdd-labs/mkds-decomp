/*
 * PURPOSE: Loads a model and its winning animation.
 * The heap ID controls the model and animation setup allocations.
 * The model data and texture data initialize the supplied model object.
 * The animation data supplies joint zero, which is registered and activated.
 */

typedef struct ModelBlock ModelBlock;
typedef struct Animation Animation;
typedef struct JNT0Block JNT0Block;
typedef struct JointAnimation JointAnimation;

extern ModelBlock *Model_CreateFromNsbmdNsbtx(
    ModelBlock *model, void *modelData, void *textureData);
extern void Model_Render(ModelBlock *model, int mode);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int enabled);
extern void Animation_CreateFrom(
    int type, Animation *animation, ModelBlock *model, int enabled,
    int heapId, void *source);
extern JNT0Block *Anim_NSBCA_LoadGetJNT0Block(void *animationData);
extern JointAnimation *JNT0_LoadJointByIdx(JNT0Block *jointBlock, int index);
extern int GetRacerAnimationIndex(int animationId);
extern void Animation_Register(
    Animation *animation, int slot, JointAnimation *joint,
    int animationIndex, int heapId);
extern void Animation_SetAt(Animation *animation, int slot);

void MaybeLoadWinModelTextureAnimationHelper_from_thumb(
    int heapId, ModelBlock *model, Animation *animation, void *modelData,
    void *textureData, void *animationData)
{
    ModelBlock *modelBlock;
    JointAnimation *joint;

    modelBlock = Model_CreateFromNsbmdNsbtx(model, modelData, textureData);
    Model_Render(model, 3);
    ModelBlock_SomeMatFn(modelBlock, 1);

    Animation_CreateFrom(0, animation, model, 1, heapId, 0);

    joint = JNT0_LoadJointByIdx(
        Anim_NSBCA_LoadGetJNT0Block(animationData), 0);
    Animation_Register(
        animation, 0, joint, GetRacerAnimationIndex(2), heapId);
    Animation_SetAt(animation, 0);
}
