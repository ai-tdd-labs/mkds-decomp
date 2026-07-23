// PURPOSE: Calculates a direction value from a point and the global object.
// The input is probably a three-component fixed-point position.
// It subtracts the global position at offset 0x24 into a temporary vector.
// The final cross-product helper probably records or consumes that direction.

typedef int fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char pad_000[0x24];
    VecFx32 f24;
    char pad_030[0x12c];
    VecFx32 f15c;
} HD4;

extern HD4 *GetGlobalHD4(void);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);

void func_02073e4c(const VecFx32 *position)
{
    VecFx32 direction;
    HD4 *hd4;

    hd4 = GetGlobalHD4();
    VecFx32_Subtract(position, &hd4->f24, &direction);
    VecFx32_CrossProduct_0(&hd4->f15c, &direction);
}
