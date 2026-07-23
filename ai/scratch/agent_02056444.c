// PURPOSE: Allocates a small holder and stores the kart appear table file buffer pointer in it.
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *path);
extern char data_0216526c[]; /* "/kart_appear.ktbl" */

void **LoadKartAppearTablePointer_from_thumb(void *heap)
{
    void **holder = (void **)Mem_AllocateHeap(heap, 4);
    *holder = FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216526c);
    return holder;
}
