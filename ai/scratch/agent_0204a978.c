/* PURPOSE: Resets an input recording buffer.
 * The record owns a buffer plus two counters and control fields.
 * The exact data format is uncertain, but nearby symbols suggest recorded input.
 * A fresh cycle clears all 0xdcc bytes before resetting the record state.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputRecord {
    u32 *buffer;
    u16 readPosition;
    u16 writePosition;
    u32 active;
    u32 bufferReady;
} InputRecord;

extern void Mem_CpuFill8(void *destination, u32 value, u32 size);

void func_0204a978(InputRecord *record)
{
    if (record->buffer == 0) {
        return;
    }

    if (record->bufferReady == 0) {
        if (record->buffer != 0) {
            Mem_CpuFill8(record->buffer, 0, 0xdcc);
        }
        record->bufferReady = 1;
    }

    record->buffer[0] = 0;
    record->bufferReady = 0;
    record->readPosition = 0;
    record->writePosition = 0;
    record->active = 1;
}
