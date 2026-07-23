// PURPOSE: Averages matching signed halfwords in two buffers.
// The destination buffer is updated in place, using the source buffer as the
// other input. The byte length is probably even, and the resulting destination
// is copied to the source buffer by the SDK helper.

typedef unsigned int u32;
typedef short s16;

extern void MIi_CpuCopyFast(const void *source, void *destination, u32 length);

void func_0212f1ac(s16 *destination, const s16 *source, u32 length)
{
    u32 count;
    int i;

    count = length >> 1;
    for (i = 0; (u32)i < count; i++) {
        destination[i] = (destination[i] + source[i] + 1) >> 1;
    }

    MIi_CpuCopyFast(destination, source, length);
}
