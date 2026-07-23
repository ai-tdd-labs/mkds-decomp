/* PURPOSE: Prepares the global ghost-loading resources.
 * The heap argument supplies the global state and its three worker resources.
 * Each resource starts an asynchronous setup task, which is allowed to finish
 * before the next resource is created. Staff ghost times are loaded last.
 */

typedef struct GlobalPK {
    void *structYE;
    void *effects;
    void *ghostHolder;
    unsigned char reserved[8];
} GlobalPK;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *AllocateStructYE(void *heap);
extern void SetStructYE_RunATFunction(void *structYE);
extern void WaitForWorkerTask(void);
extern void *AllocateFX(void *heap);
extern void RunSomeATFunction(void *effects);
extern void *AllocateGhostHolder(void *heap);
extern void RunReadGhostBinsFn(void *ghostHolder);
extern void ReadStaffGhostTimeBin(void *heap);

extern GlobalPK *data_0217d374;

void InitializeGlobalPK_from_thumb(void *heap)
{
    data_0217d374 = (GlobalPK *)Mem_AllocateHeap(heap, 0x14);

    data_0217d374->structYE = AllocateStructYE(heap);
    SetStructYE_RunATFunction(data_0217d374->structYE);
    WaitForWorkerTask();

    data_0217d374->effects = AllocateFX(heap);
    RunSomeATFunction(data_0217d374->effects);
    WaitForWorkerTask();

    data_0217d374->ghostHolder = AllocateGhostHolder(heap);
    RunReadGhostBinsFn(data_0217d374->ghostHolder);
    WaitForWorkerTask();

    ReadStaffGhostTimeBin(heap);
}
