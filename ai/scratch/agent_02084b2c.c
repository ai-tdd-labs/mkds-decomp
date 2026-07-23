// PURPOSE: Builds a model and preserves a private copy of its texture metadata.
// The caller supplies the heap, model storage, NSBMD data, and optional NSBTX data.
// The model resource is registered and its texture keys are prepared for rendering.
// Texture metadata is copied into heap-owned memory when texture data is present.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct IntrusiveListWrapper IntrusiveListWrapper;
typedef struct ModelBlock ModelBlock;

typedef struct Mdl0Block {
    u32 signature;
    u8 padding_04[0x0a];
    u16 model_dict_offset;
} Mdl0Block;

typedef struct Mdl0ModelDictionary {
    u8 padding_00[0x0c];
    u32 first_model_offset;
} Mdl0ModelDictionary;

typedef struct Tex0Block {
    u32 signature;
    u32 block_size;
    u32 tex_vram_key;
    u16 tex_data_size_bs3;
    u16 tex_dict_offset;
    u16 tex_flag;
    u16 padding_12;
    u32 tex_data_offset;
    u32 comp_tex_vram_key;
    u16 comp_tex_data_size_bs3;
    u16 comp_tex_dict_offset;
    u16 comp_tex_flag;
    u16 padding_22;
    u32 comp_tex_data_offset;
    u32 comp_tex_info_data_offset;
    u32 plt_vram_key;
    u16 plt_data_size_bs3;
    u16 plt_flag;
} Tex0Block;

typedef struct ModelResource {
    void *previous;
    void *next;
    void *nsbmd;
    Tex0Block *tex0;
} ModelResource;

typedef struct Model {
    u32 render_flags;
    ModelBlock *model_block;
    u8 padding_08[0x54];
    ModelResource resource;
} Model;

extern Mdl0Block *Nsbmd_GetMDL0Block(void *nsbmd);
extern Tex0Block *Nsbtx_GetTEX0Block(void *nsbtx);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list,
                                             void *item);
extern void Tex0Block_MaybePrepareFields(Tex0Block *tex0);
extern int func_02010168(Mdl0Block *mdl0, Tex0Block *tex0);
extern void StructML_MaybeInnerLoadModel(Model *model,
                                         ModelBlock *model_block,
                                         int reverse_cull);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Mem_CpuCopy8(const void *source, void *destination,
                         unsigned int size);

extern IntrusiveListWrapper data_0217aeb0;

ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(void *heap, Model *model,
                                               void *nsbmd, void *nsbtx)
{
    Mdl0Block *mdl0 = Nsbmd_GetMDL0Block(nsbmd);
    Tex0Block *tex0 = Nsbtx_GetTEX0Block(nsbtx);

    model->resource.tex0 = 0;
    model->resource.nsbmd = 0;
    IntrusiveListWrapper_InsertLast(&data_0217aeb0, &model->resource);
    model->resource.nsbmd = nsbmd;

    if (tex0 != 0) {
        tex0->tex_flag &= ~1;
        tex0->comp_tex_flag &= ~1;
        tex0->tex_vram_key = 0;
        tex0->comp_tex_vram_key = 0;
        tex0->plt_flag &= ~1;
        tex0->plt_vram_key = 0;
        Tex0Block_MaybePrepareFields(tex0);

        model->resource.tex0 = tex0;
        if (mdl0->signature == 0x304c444d) {
            func_02010168(mdl0, tex0);
        }
    }

    mdl0 = Nsbmd_GetMDL0Block(nsbmd);
    {
        Mdl0ModelDictionary *dictionary =
            (Mdl0ModelDictionary *)((u8 *)mdl0 + mdl0->model_dict_offset);

        StructML_MaybeInnerLoadModel(
            model, (ModelBlock *)((u8 *)mdl0 + dictionary->first_model_offset),
            1);
    }

    {
        Tex0Block *source;
        u32 size;
        ModelResource *resource;
        ModelBlock *result;

        resource = &model->resource;
        source = resource->tex0;
        result = model->model_block;

        if (source != 0) {
            size = source->tex_data_offset;
            resource->tex0 = Mem_AllocateHeap(heap, size);
            Mem_CpuCopy8(source, resource->tex0, size);
        }

        return result;
    }
}
