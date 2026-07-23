// PURPOSE: Calculates a scaled direction value for a position.
// The input is probably a three-component fixed-point position.
// It compares the position with a global object's position, then uses another
// global direction vector and its signed scale field to produce the result.

typedef int fx32;
typedef short s16;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    char pad_000[0x0c];
    VecFx32 f0c;
    char pad_018[0x0c];
    VecFx32 f24;
    char pad_030[0x23c];
    s16 f26c;
} HD4;

extern HD4 *GetGlobalHD4(void);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VecFx32_CrossProduct_0(const VecFx32 *a, const VecFx32 *b);

fx32 func_02073e04(const VecFx32 *position)
{
    VecFx32 direction;
    HD4 *hd4;

    hd4 = GetGlobalHD4();
    VecFx32_Subtract(position, &hd4->f24, &direction);
    return hd4->f26c * VecFx32_CrossProduct_0(&hd4->f0c, &direction);
}
