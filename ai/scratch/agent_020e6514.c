// PURPOSE: Builds the draw data for a billboard model.
// The first argument supplies the model resource and the third receives its draw data.
// If a texture animation is present, this creates one texture and palette entry per frame.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct ModelResourceHeader {
    u32 size;
    u32 display_list_offset;
    u32 material_set_offset;
    u32 shape_set_offset;
    u32 inverse_matrix_offset;
    u8 model_info[8];
    fx32 position_scale;
} ModelResourceHeader;

typedef struct ModelHandle {
    u32 flags;
    ModelResourceHeader *resource;
} ModelHandle;

typedef struct MaterialData {
    u32 flags;
    u32 diffuse_ambient;
    u32 specular_emission;
    u32 polygon_attributes;
    u32 reserved_10;
    u32 texture_parameters;
    u32 reserved_18;
    u16 palette_parameters;
} MaterialData;

typedef struct ShapeData {
    u32 reserved_00[2];
    u32 display_list_offset;
    u32 display_list_length;
} ShapeData;

typedef struct MaterialAnimationResult {
    u32 flags;
    u32 diffuse_ambient;
    u32 specular_emission;
    u32 polygon_attributes;
    u32 texture_parameters;
    u32 palette_parameters;
    u8 reserved_18[0x20];
} MaterialAnimationResult;

typedef struct AnimationObject {
    fx32 frame;
} AnimationObject;

typedef struct Animation {
    u16 loop_mode;
    u16 ended;
    fx32 length;
    fx32 speed;
    fx32 frame;
    u16 loop_iteration;
    u16 loop_count;
    ModelHandle *model;
    u16 animation_count;
    u16 current_animation;
    AnimationObject **objects;
} Animation;

typedef struct BillboardDrawData {
    void *display_list;
    u32 display_list_length;
    fx32 position_scale;
    u32 diffuse_ambient;
    u32 specular_emission;
    u32 polygon_attributes;
    u16 texture_index;
    u16 texture_count;
    u32 *texture_parameters;
    u32 *palette_parameters;
} BillboardDrawData;

extern u32 Animation_GetCurrentLength(void *animation);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Anim_UnkFnPtr_BTP(
    MaterialAnimationResult *result, AnimationObject *object, u32 index);

void func_020e6514(
    ModelHandle *model, Animation *animation, BillboardDrawData *draw)
{
    u32 texture_bits;
    u32 animation_index;
    MaterialAnimationResult result;
    u8 *resource;
    u8 *section;
    ShapeData *shape;
    u16 texture_count;
    u32 allocation_size;
    u16 frame;
    MaterialData *material;

    resource = (u8 *)model->resource;

    section = resource + ((ModelResourceHeader *)resource)->material_set_offset;
    material = (MaterialData *)(section +
        *(u32 *)(section + *(u16 *)(section + 0xa) + 8));

    section = resource + ((ModelResourceHeader *)resource)->shape_set_offset;
    shape = (ShapeData *)(section +
        *(u32 *)(section + *(u16 *)(section + 6) + 4));

    draw->display_list = (u8 *)shape + shape->display_list_offset;
    draw->display_list_length = shape->display_list_length;
    draw->position_scale = model->resource->position_scale;
    draw->diffuse_ambient = material->diffuse_ambient;
    draw->specular_emission = material->specular_emission;
    draw->polygon_attributes = material->polygon_attributes & ~0xf;
    draw->texture_index = 0;

    if (animation != 0) {
        texture_bits = material->texture_parameters;
        texture_count =
            (Animation_GetCurrentLength(animation) << 4) >> 16;
        draw->texture_count = texture_count;

        allocation_size = texture_count * sizeof(u32);
        draw->texture_parameters = Mem_AllocateHeap(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
            allocation_size);
        draw->palette_parameters = Mem_AllocateHeap(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
            allocation_size);

        animation_index = 0;
        texture_bits &= 0xc00f0000;
        for (frame = 0; frame < texture_count; frame++) {
            animation->frame = (u32)frame << 12;
            animation->objects[animation->current_animation]->frame =
                animation->frame;

            Anim_UnkFnPtr_BTP(
                &result, animation->objects[0], animation_index);

            draw->texture_parameters[frame] =
                result.texture_parameters & 0x3ff0ffff;
            draw->texture_parameters[frame] |= texture_bits;
            draw->palette_parameters[frame] = result.palette_parameters;
        }
        return;
    }

    draw->texture_count = 1;
    draw->texture_parameters = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 4);
    draw->palette_parameters = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 4);
    draw->texture_parameters[0] = material->texture_parameters;
    draw->palette_parameters[0] = material->palette_parameters;
}
