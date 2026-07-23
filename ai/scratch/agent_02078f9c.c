/* PURPOSE: Load the kart-select model resources and build the model block for the current kart.
 *
 * CreateCEML_from_thumb(heap): reads the "kart/select/select.nsbmd" and
 * "kart/select/select.nsbtx" model-menu files into two stack buffers,
 * allocates 0x6c bytes for a new model block on heap and stores it into
 * data_0217ad08's +0x1cc field, then builds the model from the two files,
 * renders it once (mode 2) and marks its materials somehow-translucent.
 */

typedef unsigned char u8;

typedef struct StructCE {
    u8 pad_00[0x1cc];
    void *modelHolder; /* 0x1cc */
} StructCE;

typedef struct ModelBlock {
    u8 pad_00[4];
    void *f4; /* 0x4 */
} ModelBlock;

extern StructCE *data_0217ad08;
extern char data_02165760[]; /* "kart/select/select.nsbmd" */
extern char data_0216577c[]; /* "kart/select/select.nsbtx" */

extern void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Model_CreateFromNsbmdNsbtx(void *modelHolder, void *nsbmd, void *nsbtx);
extern void Model_Render(void *model, int mode);
extern void ModelBlock_SetSomethingToAllMaterials_MaybeTraslucent(ModelBlock *model, int arg1);

void CreateCEML_from_thumb(void *heap)
{
    void *nsbmd;
    void *nsbtx;

    ReadKartModelMenuFile_from_thumb(heap, data_02165760, &nsbmd);
    ReadKartModelMenuFile_from_thumb(heap, data_0216577c, &nsbtx);

    data_0217ad08->modelHolder = Mem_AllocateHeap(heap, 0x6c);
    Model_CreateFromNsbmdNsbtx(data_0217ad08->modelHolder, nsbmd, nsbtx);
    Model_Render(data_0217ad08->modelHolder, 2);
    ModelBlock_SetSomethingToAllMaterials_MaybeTraslucent(
        ((ModelBlock *)data_0217ad08->modelHolder)->f4, 1);
}
