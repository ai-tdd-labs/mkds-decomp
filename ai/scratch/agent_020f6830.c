// PURPOSE: Updates an object's motion value from two direction vectors.

typedef int fx32;
typedef long long fx64;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char _00[0x7C];
    fx32 value;
    char _80[0x28];
} ScaleEntry;

typedef struct {
    char _00[0x44];
    unsigned int tableIndex;
    char _48[0x24];
    int previous;
    int current;
    char _74[0x8C];
    fx32 motion;
} Object;

extern ScaleEntry *data_0217bc34;
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);

void func_020f6830(Object *object, const VecFx32 *a, const VecFx32 *b)
{
    int difference;
    fx32 value;

    difference = object->current - object->previous;
    if (difference * difference >= 0x68BE1) {
        return;
    }

    value = VecFx32_CrossProduct_0(a, b);
    if (value <= 0) {
        value = -value;
    }

    object->motion = (fx32)(((fx64)value
        * data_0217bc34[object->tableIndex].value) >> 12);
    object->motion >>= 1;
}
