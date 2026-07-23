/* PURPOSE: Copies or clears a safe section of a memory image.
 * The context probably describes source and destination image bases plus a valid range.
 * The requested byte range is clipped to both 0x4000..0x8000 and the context range.
 * A nonzero final argument clears the destination; zero copies from the source.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RangeTransferContext {
    u32 validStart;
    const u8 *sourceBase;
    u8 *destinationBase;
    u32 validLength;
} RangeTransferContext;

extern void Mem_CpuFill8(void *destination, u32 value, u32 size);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_0200850c(RangeTransferContext *context, u32 requestedStart,
                   u32 requestedEnd, int clearDestination) {
    u32 copyStart = requestedStart;

    if (copyStart < 0x4000) {
        copyStart = 0x4000;
    }
    if (requestedEnd > 0x8000) {
        requestedEnd = 0x8000;
    }
    if (copyStart < context->validStart) {
        copyStart = context->validStart;
    }
    if (requestedEnd > context->validStart + context->validLength) {
        requestedEnd = context->validStart + context->validLength;
    }

    if (copyStart < requestedEnd) {
        if (clearDestination != 0) {
            Mem_CpuFill8(context->destinationBase + copyStart, 0,
                         requestedEnd - copyStart);
        } else {
            Mem_CpuCopy8(context->sourceBase + copyStart,
                         context->destinationBase + copyStart,
                         requestedEnd - copyStart);
        }
    }
}
