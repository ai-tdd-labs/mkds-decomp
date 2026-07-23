/* PURPOSE: Builds a lookup table for the course's cannon points.
 *
 * Takes no arguments and clears the table when the course has no cannon points.
 * Otherwise, allocates one entry per point and maps each cannon ID to its
 * position in the loaded KTPC list.
 */

typedef struct NkmCannonPoint {
    unsigned char pad_00[0x1a];
    unsigned short cannonIndex;
} NkmCannonPoint;

typedef struct CoursePathState {
    unsigned char pad_000[0x34];
    NkmCannonPoint *ktpcEntries;
    unsigned short ktpcEntryCount;
    unsigned char pad_03a[0xc2];
    unsigned short *cannonIndexTable;
} CoursePathState;

extern CoursePathState *data_02175620;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void InitializePECannonTable_from_thumb(void)
{
    unsigned short entryCount = data_02175620->ktpcEntryCount;
    unsigned short entryIndex;

    if (entryCount == 0) {
        data_02175620->cannonIndexTable = 0;
        return;
    }

    data_02175620->cannonIndexTable = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        entryCount * sizeof(unsigned short));

    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
        unsigned short cannonIndex =
            data_02175620->ktpcEntries[entryIndex].cannonIndex;

        data_02175620->cannonIndexTable[cannonIndex] = entryIndex;
    }
}
