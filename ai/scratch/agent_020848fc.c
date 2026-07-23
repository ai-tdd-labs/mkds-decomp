// PURPOSE: Releases every loaded model resource in the global list.
// The list entries probably hold a common header-file resource at offset 8.
// Each non-null resource is passed to the common disposal routine.

typedef struct ModelResourceEntry {
    unsigned char pad00[8];
    void *resource;
} ModelResourceEntry;

extern ModelResourceEntry *IntrusiveListWrapper_NextItem(void *list, void *item);
extern void MaybeDisposeCommonHeaderFileData(void *resource);
extern unsigned char data_0217aeb0[];

void DisposeAllModelResources(void)
{
    ModelResourceEntry *entry;

    entry = IntrusiveListWrapper_NextItem(data_0217aeb0, 0);
    if (entry == 0) {
        return;
    }

    do {
        if (entry->resource != 0) {
            MaybeDisposeCommonHeaderFileData(entry->resource);
        }
        entry = IntrusiveListWrapper_NextItem(data_0217aeb0, entry);
    } while (entry != 0);
}
