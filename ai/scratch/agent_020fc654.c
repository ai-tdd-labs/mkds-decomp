// PURPOSE: Moves an object along a gently waving path.
// The object supplies the path origin, direction, wave phase, and current position.
// One mode eases the whole position toward the path; the other eases only height.

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct PathObject {
    u8 pad_000[0x50];
    VecFx32 origin_050;
    fx32 field_05c;
    fx32 vertical_velocity_060;
    u8 pad_064[0x74 - 0x64];
    unsigned int flags_074;
    u8 pad_078[0xc4 - 0x78];
    VecFx32 position_0c4;
    u8 pad_0d0[0xf0 - 0xd0];
    VecFx32 direction_0f0;
    u8 pad_0fc[0x260 - 0xfc];
    fx32 path_offset_260;
    fx32 wave_scale_264;
    u16 phase_268;
} PathObject;

extern const s16 data_0215d4b4[];
extern void VecFx32_AddScale1(fx32 scale, const VecFx32 *direction,
                              const VecFx32 *origin, VecFx32 *out);
extern void VecFx32_Subtract(const VecFx32 *left, const VecFx32 *right,
                             VecFx32 *out);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b)) >> 12))

void func_020fc654(PathObject *object)
{
    VecFx32 next;
    fx32 pathOffset = object->path_offset_260;

    if (object->flags_074 & 0x40000000) {
        object->phase_268 += 0x5dc;
        VecFx32_AddScale1(
            pathOffset
                + FX_MUL(object->wave_scale_264,
                         data_0215d4b4[(object->phase_268 >> 4) << 1]),
            &object->direction_0f0, &object->origin_050, &next);
        VecFx32_Subtract(&next, &object->position_0c4, &next);
        VecFx32_AddScale1(0x333, &next, &object->position_0c4,
                          &object->position_0c4);
        return;
    }

    object->position_0c4.y += object->vertical_velocity_060 >> 1;
    object->phase_268 += 0x5dc;
    object->position_0c4.y +=
        (fx32)(((fx64)(pathOffset
                          + FX_MUL(object->wave_scale_264,
                                   data_0215d4b4[(object->phase_268 >> 4) << 1])
                          + object->origin_050.y
                          - object->position_0c4.y)
                  * (fx64)0x19a)
                 >> 12);
    object->position_0c4.x = object->origin_050.x;
    object->position_0c4.z = object->origin_050.z;
}
