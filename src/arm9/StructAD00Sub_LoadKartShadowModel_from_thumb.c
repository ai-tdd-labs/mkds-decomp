// PURPOSE: Loads a kart's shadow model into its shadow data block.
// The first argument supplies the kart index and receives the allocated shadow block.
// The second argument is the heap used for allocation.
// The final setup probably connects the model's first shadow node.

extern char *FormatKartShadowNsbmdPath(int kart);
extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void LoadedModelTexture_SomeFn(void *model, void *nsbmd, void *nsbtx);
extern void *Nsbmd_GetMDL0Block(void *nsbmd);
extern void StructAD00Sh_SomeFn(void *shadow, void *node, int arg2);

void StructAD00Sub_LoadKartShadowModel_from_thumb(int *a1, void *a2)
{
    void *nsbmd;
    void *mdl0;

    nsbmd = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
        FormatKartShadowNsbmdPath((unsigned short)a1[1]));

    a1[7] = (int)Mem_AllocateHeap(a2, 0x74);
    LoadedModelTexture_SomeFn((char *)a1[7] + 0x5c, nsbmd, nsbmd);

    mdl0 = Nsbmd_GetMDL0Block(nsbmd);
    StructAD00Sh_SomeFn(
        (void *)a1[7],
        (char *)mdl0 + *(int *)((char *)mdl0 + *(unsigned short *)((char *)mdl0 + 0xe) + 0xc),
        3);
}
