/* PURPOSE: Sets up the save-data I/O manager.
 *
 * The heap argument provides storage for the global manager and, unless the
 * shared mode flag is two, its two probably temporary I/O buffers.
 */

typedef struct SaveDataIoManager {
    char pad_00[0xc];
    int state;
    char pad_10[0x50];
    void *buffer;
    void *smallBuffer;
} SaveDataIoManager;

extern SaveDataIoManager *data_021759d4;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size,
                                     unsigned int alignment);

void InitializeSaveDataIoManager_from_thumb(void *heap)
{
    data_021759d4 = (SaveDataIoManager *)Mem_AllocateHeap(heap, 0x70);

    if (*(volatile unsigned short *)0x027ffc40 != 2) {
        data_021759d4->buffer = Mem_AllocateHeapAligned(heap, 0x2c00, 0x20);
        data_021759d4->smallBuffer = Mem_AllocateHeapAligned(heap, 1, 0x20);
    }

    data_021759d4->state = 0;
}
