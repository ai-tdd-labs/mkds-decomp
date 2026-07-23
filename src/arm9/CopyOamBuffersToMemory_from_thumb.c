/* PURPOSE: Copies prepared sprite buffers into OAM memory.
 * The first argument supplies the main-engine sprite buffer.
 * The second argument supplies the sub-engine sprite buffer.
 * Each non-null buffer is flushed before its full contents are copied.
 */

typedef unsigned int u32;

extern void Arm_FlushRange(void *buffer, u32 size);
extern void CopyToOamA(void *source, u32 offset, u32 size);
extern void CopyToOamB(void *source, u32 offset, u32 size);

void CopyOamBuffersToMemory_from_thumb(void *main_buffer, void *sub_buffer)
{
    if (main_buffer != 0) {
        Arm_FlushRange(main_buffer, 0x400);
        CopyToOamA(main_buffer, 0, 0x400);
    }

    if (sub_buffer != 0) {
        Arm_FlushRange(sub_buffer, 0x400);
        CopyToOamB(sub_buffer, 0, 0x400);
    }
}
