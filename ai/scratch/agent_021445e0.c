// PURPOSE: Counts selected bits and scales the result by a stored value.
/*
 * The first argument probably points to an object with a halfword at 0x810.
 * The second argument is masked to the requested bit width before counting.
 * The count is multiplied by that halfword and added to the third argument.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    unsigned char padding[0x810];
    u16 multiplier;
} BitCountSource;

extern u32 Math_CountPopulation(u32 value);

u32 func_021445e0(BitCountSource *source, u32 value, u32 base, u32 width)
{
    return source->multiplier * Math_CountPopulation(value & ((1U << width) - 1)) + base;
}
