/* PURPOSE: Builds an object's output transform matrix.
 * The object position is converted to matrix translation units by shifting
 * each coordinate right by four. The complete 4x3 transform is copied to the
 * output, then its 3x3 rotation portion is combined with a global matrix.
 */

typedef int fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    fx32 m[3][3];
} MtxFx33;

typedef struct {
    MtxFx33 rotation;
    VecFx32 translation;
} MtxFx43;

typedef struct {
    unsigned char _pad00[0x94];
    MtxFx43 transform;
    unsigned char _padc4[0xc];
    const VecFx32 *position;
} TransformObject;

extern MtxFx33 data_0217c600;
extern void MTX_Concat33(const MtxFx33 *left, const MtxFx33 *right,
                         MtxFx33 *result);

void func_020ff910(TransformObject *object, MtxFx43 *output)
{
    const VecFx32 *position = object->position;

    object->transform.translation.x = position->x >> 4;
    object->transform.translation.y = position->y >> 4;
    object->transform.translation.z = position->z >> 4;

    *output = object->transform;
    MTX_Concat33(&data_0217c600, &output->rotation, &output->rotation);
}
