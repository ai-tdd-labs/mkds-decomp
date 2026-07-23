// PURPOSE: Allocates and initializes a billboard model from model and texture-pattern resources.

typedef unsigned int u32;

typedef struct BillboardModel {
    u32 unk_00[4];
    u32 flags_10;
    u32 flags_14;
} BillboardModel;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FindItemFileBuffer_from_thumb(void *item);
extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    BillboardModel *model, void *nsbmd, void *nsbtp, int unused);

void *CreateBillboardModel_from_thumb(void *modelItem, void *animationItem)
{
    BillboardModel *model;
    void *nsbmd;
    void *nsbtp;

    model = (BillboardModel *)Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x2c);
    nsbmd = FindItemFileBuffer_from_thumb(modelItem);
    nsbtp = FindItemFileBuffer_from_thumb(animationItem);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(model, nsbmd, nsbtp, 0);

    model->flags_14 &= 0xC0FFFFFF;
    model->flags_14 |= 0x04000000;
    model->flags_14 &= ~0xF;
    model->flags_14 |= 2;
    model->flags_10 &= 0x8000FFFF;
    model->flags_10 |= 0x10840000;
    return model;
}
