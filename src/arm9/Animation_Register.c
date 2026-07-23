// PURPOSE: Registers an animation block in a selected slot.
// The animation, slot, joint data, and animation index describe the entry.
// A nonzero heap probably allocates storage; otherwise existing slot storage is used.

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
    u32 unknown_18;
    void **blocks;
    int *animationIndices;
} Animation;

extern u32 data_0217af20;
extern u32 Anim_GetNeededBlockSize(void *joint, void *resourceData);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void MaybeCreateAnimationBlock(
    void *block, void *joint, void *resourceData, void *unknown);

void Animation_Register(
    Animation *animation, int slot, void *joint, int animationIndex, void *heap)
{
    void *block;

    if (heap == 0) {
        block = animation->blocks[slot];
        animation->animationIndices[slot] = animationIndex;
    } else {
        data_0217af20 = Anim_GetNeededBlockSize(joint, animation->resource->unknown_04);
        block = Mem_AllocateHeap(heap, data_0217af20);
        animation->blocks[slot] = block;
        animation->animationIndices[slot] = animationIndex;
    }

    MaybeCreateAnimationBlock(
        block, joint, animation->resource->unknown_04, animation->resource->unknown_68);
}
