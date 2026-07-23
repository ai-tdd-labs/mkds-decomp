/* PURPOSE: Finds an animation block with a requested type.
 * The animation file must have the expected file magic before it is searched.
 * Each block is checked in order, and the matching block is returned.
 * Returns null when the file magic is wrong or no matching block exists.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AnimationFileHeader {
    u32 magic;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 blockCount;
} AnimationFileHeader;

typedef struct AnimationBlock {
    u32 magic;
} AnimationBlock;

extern AnimationBlock *Anim_GetBlock(AnimationFileHeader *animation,
                                     unsigned int blockIndex);

AnimationBlock *Anim_LoadFindAnimationBlock(AnimationFileHeader *animation,
                                             unsigned int fileMagic,
                                             unsigned int blockMagic)
{
    unsigned int blockIndex;

    if (animation->magic != fileMagic) {
        goto not_found;
    }

    for (blockIndex = 0; blockIndex < animation->blockCount; blockIndex++) {
        AnimationBlock *block = Anim_GetBlock(animation, blockIndex);

        if (block->magic == blockMagic) {
            return block;
        }
    }

not_found:
    return 0;
}
