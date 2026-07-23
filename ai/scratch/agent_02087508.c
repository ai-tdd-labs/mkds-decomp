// PURPOSE: Creates the AER state and its four default data blocks.
// The destination receives the new state, the second argument is its identifier,
// and the third argument selects the heap used for the backing allocation.
// The exact purpose of the copied default blocks is probably AER configuration.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct AERHeader {
    u32 words[3];
} AERHeader;

typedef struct AERBlock {
    u32 words[9];
} AERBlock;

typedef struct StructAER {
    AERHeader header;
    u16 identifier;
    u16 pad_0e;
    u32 enabled;
    u32 state;
    u32 active;
    AERBlock *blocks;
    u16 value20;
    u16 value22;
    u16 value24;
    u16 value26;
} StructAER;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern AERHeader data_02155ccc;
extern AERBlock data_021659ec;
extern AERBlock data_02165a34;
extern AERBlock data_02165a10;
extern AERBlock data_02165a58;

void StructAER_SomeFn_from_thumb(StructAER *aer, u16 identifier, void *heap)
{
    aer->blocks = Mem_AllocateHeap(heap, 0x90);
    aer->header = data_02155ccc;
    aer->identifier = identifier;
    aer->blocks[0] = data_021659ec;
    aer->blocks[1] = data_02165a34;
    aer->blocks[2] = data_02165a10;
    aer->blocks[3] = data_02165a58;
    aer->enabled = 1;
    aer->state = 0;
    aer->active = 1;
    aer->value24 = 0;
    aer->value26 = 0x7fff;
    aer->value22 = 0;
    aer->value20 = 0;
}
