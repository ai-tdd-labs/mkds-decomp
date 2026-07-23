// PURPOSE: Builds lookup tables for the loaded resource entries.

#pragma optimize_for_size on

typedef unsigned short u16;

typedef struct ResourceEntry {
    unsigned char _00[0xa0];
    u16 id;
    u16 value;
} ResourceEntry;

typedef struct ResourceEntryList {
    ResourceEntry **entries;
    u16 count;
} ResourceEntryList;

extern ResourceEntryList *data_0217b864;
extern u16 *data_0217b868;
extern void **data_0217b86c;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void func_020e730c(void)
{
    u16 count;
    int i;

    count = data_0217b864->count;
    data_0217b86c = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        (unsigned int)count << 2);
    data_0217b868 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        (unsigned int)count << 1);

    for (i = 0; i < data_0217b864->count; i++) {
        ResourceEntry *entry = data_0217b864->entries[i];
        u16 id = entry->id;

        data_0217b86c[id] = (void *)entry + 4;
        data_0217b868[id] = entry->value;
    }
}
