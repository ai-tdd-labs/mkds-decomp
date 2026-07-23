// PURPOSE: Allocates and initializes space for a group of entries.
// The first two descriptors provide entry counts at offset six.
// Their combined count determines the allocation size when the second exists.
// The allocated pointer is stored through output before initialization.

typedef unsigned short u16;

typedef struct EntryDescriptor {
    unsigned char unknown_00[6];
    u16 count;
} EntryDescriptor;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void func_02124efc(void *entries, u16 count);

void func_02124ed0(void *heap, EntryDescriptor *first,
                   EntryDescriptor *second, void **output)
{
    u16 count = first->count;

    if (second != 0) {
        count += second->count;
    }

    *output = Mem_AllocateHeap(heap, count << 6);
    func_02124efc(*output, count);
}
