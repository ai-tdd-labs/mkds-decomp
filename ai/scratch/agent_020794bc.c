/*
 * PURPOSE: Loads a racer's kart 3D model (mesh + texture) and wires it into
 * the kart's model block, optionally registering its wheel/tire node.
 *
 * Arguments:
 *   a1 - pointer to a kart data struct; a1[1] (offset 4) holds the character
 *        id used to build the nsbmd/nsbtx file paths, a1[5] (offset 0x14)
 *        receives the loaded ModelBlock pointer.
 *   a2 - heap id, forwarded to Mem_AllocateHeap and Model_CreateFromNsbmdNsbtxMetaCopy.
 *   a3 - flag: when nonzero, looks up the "kart_tire" node in the model's
 *        dictionary and stores it into RacerManager.sh (data_0217ad00+0xc).
 *
 * After building the model it renders it once (probably to force material
 * setup), calls a material-related setup function, and finally loads the
 * kart body palette using data from data_0217ad00+0x10.
 */

typedef struct ModelBlock ModelBlock;

extern char *FormatCharacterKartNsbmdPath(int character);
extern char *FormatCharacterKartNsbtxPath(int character);
extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *Mem_AllocateHeap(int heapId, int size);
extern ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(int heapId, void *modelMem, void *nsbmd, void *nsbtx);
extern void Model_Render(ModelBlock *model, int arg1);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int arg1);
extern int Dict_SomeFn_0(void *dict, char *name);
extern void func_02013468(ModelBlock *model, int i, int arg1);
extern void LoadKartBodyPalette_from_thumb(void *model, int character, int arg2);

extern char data_021550b8[];  /* "kart_tire" */
extern int *data_0217ad00;    /* pointer to RacerManager (dereferenced) */

void StructAD00Sub_LoadKartModel_from_thumb(int *a1, int a2, int a3)
{
    unsigned short character;
    void *nsbmd;
    void *nsbtx;
    ModelBlock *model;
    int tireIdx;

    character = (unsigned short)a1[1];

    nsbmd = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(FormatCharacterKartNsbmdPath(character));
    nsbtx = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(FormatCharacterKartNsbtxPath(character));

    a1[5] = (int)Mem_AllocateHeap(a2, 0x6c);

    model = Model_CreateFromNsbmdNsbtxMetaCopy(a2, (void *)a1[5], nsbmd, nsbtx);

    Model_Render((ModelBlock *)a1[5], 3);
    ModelBlock_SomeMatFn(model, 0);

    if (a3 != 0) {
        tireIdx = Dict_SomeFn_0((char *)model + *(int *)((char *)model + 8) + 4, data_021550b8);
        func_02013468(model, tireIdx, 0);
        data_0217ad00[3] = tireIdx;
    }

    LoadKartBodyPalette_from_thumb((void *)a1[5], a1[1], data_0217ad00[4]);
}
