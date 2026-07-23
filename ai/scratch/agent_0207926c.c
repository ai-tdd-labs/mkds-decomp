// PURPOSE: Loads the tire model for a character's kart.
// The kart record supplies the character id and receives the model memory.
// The heap is used for the model allocation and construction.
// The final calls probably prepare the tire model's materials for rendering.

typedef struct ModelBlock ModelBlock;

extern char *FormatKartTireNsbmdPath(int character, int kart);
extern char *FormatKartTireNsbtxPath(int character, int kart);
extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(void *heap, void *modelMem, void *nsbmd, void *nsbtx);
extern void Model_Render(ModelBlock *model, int arg1);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int arg1);

void CharacterKart_LoadKartTireModel_from_thumb(int *a1, void *a2)
{
    unsigned short character;
    void *nsbmd;
    void *nsbtx;
    ModelBlock *model;

    character = (unsigned short)a1[1];
    nsbmd = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
        FormatKartTireNsbmdPath(character, a1[8]));
    nsbtx = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(
        FormatKartTireNsbtxPath(character, a1[8]));
    a1[6] = (int)Mem_AllocateHeap(a2, 0x6c);
    model = Model_CreateFromNsbmdNsbtxMetaCopy(a2, (void *)a1[6], nsbmd, nsbtx);
    Model_Render((ModelBlock *)a1[6], 3);
    ModelBlock_SomeMatFn(model, 0);
}
