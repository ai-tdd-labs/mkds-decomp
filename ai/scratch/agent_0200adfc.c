/* PURPOSE: Copies bytes from a cached range when the request is available.
 * The first argument owns four cached ranges, while the other arguments give
 * the requested offset, destination, and byte count. Interrupts are disabled
 * during the search; a successful copy also marks the owner as active.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CachedRange {
    int start;
    u32 size;
    u8 *data;
    u32 state;
} CachedRange;

typedef struct RangeCache {
    int active;
    u8 unknown04[0x2c];
    CachedRange ranges[4];
} RangeCache;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_0200adfc(RangeCache *cache, int requestStart, void *destination,
                  u32 requestSize)
{
    int copied = 0;
    u32 irqState = Os_DisableIrq();
    CachedRange *range = cache->ranges;

    while (range < cache->ranges + 4) {
        if (range->state >= 2) {
            int rangeOffset = requestStart - range->start;

            if (rangeOffset >= 0 && rangeOffset + requestSize <= range->size) {
                Mem_CpuCopy8(range->data + rangeOffset, destination, requestSize);
                copied = 1;
                cache->active = copied;
                break;
            }
        }
        range++;
    }

    Os_RestoreIrq(irqState);
    return copied;
}
