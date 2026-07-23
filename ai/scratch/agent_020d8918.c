// PURPOSE: Interpolates a path point and calculates its scaled direction.
// The first argument selects an entry from a table of paired vectors.
// The second argument receives the interpolated point, and the third receives
// the scaled difference between the pair, probably flipped by the final flag.

typedef int fx32;
typedef long long s64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct PathVectorPair {
    VecFx32 first;
    unsigned char pad0c[0x24 - 0x0c];
    VecFx32 second;
    unsigned char pad30[0x54 - 0x30];
} PathVectorPair;

typedef struct PathVectorTable {
    PathVectorPair *entries;
} PathVectorTable;

typedef struct PathVectorCursor {
    PathVectorTable *table;
    unsigned char pad04[0x0c - 0x04];
    int index;
    fx32 scale;
    fx32 blend;
    int keepDirection;
} PathVectorCursor;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);

#define MUL_FX24(a, b) ((fx32)(((s64)(a) * (b)) >> 24))

void func_020d8918(PathVectorCursor *cursor, VecFx32 *point,
                   VecFx32 *direction)
{
    PathVectorPair *pair = &cursor->table->entries[cursor->index];
    fx32 blend = cursor->blend;
    fx32 inverseBlend = 0x1000000 - blend;

    point->x = MUL_FX24(pair->first.x, inverseBlend);
    point->y = MUL_FX24(pair->first.y, inverseBlend);
    point->z = MUL_FX24(pair->first.z, inverseBlend);

    point->x += MUL_FX24(pair->second.x, blend);
    point->y += MUL_FX24(pair->second.y, blend);
    point->z += MUL_FX24(pair->second.z, blend);

    VecFx32_Subtract(&pair->second, &pair->first, direction);

    {
        fx32 scale = cursor->scale;
        direction->x = MUL_FX24(direction->x, scale);
        direction->y = MUL_FX24(direction->y, scale);
        direction->z = MUL_FX24(direction->z, scale);
    }

    if (cursor->keepDirection != 0) {
        return;
    }

    direction->x = -direction->x;
    direction->y = -direction->y;
    direction->z = -direction->z;
}
