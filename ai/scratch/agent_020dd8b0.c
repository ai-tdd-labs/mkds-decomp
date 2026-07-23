// PURPOSE: Builds a row of evenly spaced movement points.

typedef int fx32;
typedef long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct PointBuilder {
    char _00[0x20];
    int pointCount;
    fx32 scale;
    char _28[0x1c];
    VecFx32 *points;
    VecFx32 *vectors;
} PointBuilder;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VecFx32_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx64 Multiply64(fx64 left, fx64 right);

void func_020dd8b0(PointBuilder *builder, const VecFx32 *first,
                   const VecFx32 *last)
{
    VecFx32 delta;
    int i;

    VecFx32_Subtract(last, first, &delta);
    delta.x = (fx32)(Multiply64(delta.x, builder->scale) >> 12);
    delta.y = (fx32)(Multiply64(delta.y, builder->scale) >> 12);
    delta.z = (fx32)(Multiply64(delta.z, builder->scale) >> 12);

    builder->points[0] = *first;
    builder->vectors[0].x = 0;
    builder->vectors[0].y = 0;
    builder->vectors[0].z = 0;

    i = 1;
    if (i < builder->pointCount) {
        do {
            VecFx32_Add(&builder->points[i - 1], &delta, &builder->points[i]);
            builder->vectors[i].x = 0;
            builder->vectors[i].y = 0;
            builder->vectors[i].z = 0;
            i++;
        } while (i < builder->pointCount);
    }
}
