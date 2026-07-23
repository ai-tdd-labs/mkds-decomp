// PURPOSE: Checks whether two flag values form a valid change.
// The two arguments probably point to four-byte flag values.
// It first runs a shared validation step, then compares copied flag words.
// A change is accepted only when it sets a bit not already present.

typedef unsigned int u32;

extern int func_02151620(const void *first, const void *second);
extern void Mem_CpuCopy8(const void *src, void *dst, u32 size);

int func_02151640(const void *first, const void *second)
{
    u32 first_flags;
    u32 second_flags;

    if (func_02151620(first, second) == 0) {
        return 0;
    }

    Mem_CpuCopy8(first, &first_flags, 4);
    Mem_CpuCopy8(second, &second_flags, 4);

    if ((first_flags | second_flags) == ~1U) {
        return 0;
    }

    if ((first_flags & ~second_flags) == 0) {
        return 0;
    }

    return 1;
}
