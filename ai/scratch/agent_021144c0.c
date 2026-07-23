/*
 * PURPOSE: Loads the emblem graphics resources.
 * The heap argument supplies storage for a small resource record and its
 * backing buffer. The remaining fields probably hold decoded file data and
 * the embedded emblem2.bin asset.
 */

typedef struct Emblem2Resources {
    void *reserved;
    void *buffer;
    void *decodedData;
    void *fileData;
} Emblem2Resources;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *func_0205eda0(void *heap);
extern void *find_buf_fn_from_thumb(char *name);

extern Emblem2Resources *data_0217d34c;
extern char data_0216d3e4[];

void Maybe_emblem2(void *heap)
{
    data_0217d34c = Mem_AllocateHeap(heap, 0x10);
    data_0217d34c->buffer = Mem_AllocateHeap(heap, 0x78);
    data_0217d34c->decodedData = func_0205eda0(heap);
    data_0217d34c->fileData = find_buf_fn_from_thumb(data_0216d3e4);
}
