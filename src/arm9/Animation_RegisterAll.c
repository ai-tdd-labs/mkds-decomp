// PURPOSE: Registers every animation entry from a resource.
// The animation selects the resource format and owns the destination arrays.
// Each decoded entry is probably attached to the model resource.
// A null heap reuses the block already stored in the corresponding slot.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AnimationResource {
    u32 unknown_00;
    void *unknown_04;
    u32 unknown_08[24];
    void *unknown_68;
} AnimationResource;

typedef struct Animation {
    u32 unknown_00[5];
    AnimationResource *resource;
    u16 jointCount;
    u16 padding_1a;
    void **blocks;
    int *animationIndices;
    u32 unknown_24;
    u32 animationType;
} Animation;

extern u32 data_0217af20;

extern void *Anim_NSBCA_LoadGetJNT0Block(void *resourceData);
extern void *JNT0_LoadJointByIdx(void *jnt0, int index);
extern void *MaybeLoadBTP0Format(void *resourceData);
extern void *BTP0_LoadRawData(void *btp0, int index);
extern void *MaybeLoadBTA0Format(void *resourceData);
extern void *BTA0_LoadRawData(void *bta0, int index);
extern void *MaybeLoadBVA0Format(void *resourceData);
extern void *BVA0_LoadRawData(void *bva0, int index);
extern void *MaybeLoadBMA0Format(void *resourceData);
extern void *BMA0_LoadRawData(void *bma0, int index);
extern u32 Anim_GetNeededBlockSize(void *joint, void *resourceData);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void MaybeCreateAnimationBlock(
    void *block, void *joint, void *resourceData, void *unknown);

void Animation_RegisterAll(
    Animation *animation, void *resourceData, void *heap)
{
    void *joint = 0;
    u8 i;
    void *block;

    for (i = 0; i < animation->jointCount; i++) {
        switch (animation->animationType) {
        case 0:
            joint = JNT0_LoadJointByIdx(
                Anim_NSBCA_LoadGetJNT0Block(resourceData), i);
            break;
        case 2:
            joint = BTP0_LoadRawData(MaybeLoadBTP0Format(resourceData), i);
            break;
        case 1:
            joint = BTA0_LoadRawData(MaybeLoadBTA0Format(resourceData), i);
            break;
        case 3:
            joint = BVA0_LoadRawData(MaybeLoadBVA0Format(resourceData), i);
            break;
        case 4:
            joint = BMA0_LoadRawData(MaybeLoadBMA0Format(resourceData), i);
            break;
        }

        if (heap != 0) {
            data_0217af20 = Anim_GetNeededBlockSize(
                joint, animation->resource->unknown_04);
            block = Mem_AllocateHeap(heap, data_0217af20);
            animation->blocks[i] = block;
            animation->animationIndices[i] = 0;
        } else {
            block = animation->blocks[i];
            animation->animationIndices[i] = 0;
        }

        MaybeCreateAnimationBlock(
            block, joint, animation->resource->unknown_04,
            animation->resource->unknown_68);
    }
}
