// PURPOSE: Loads the shadow models used by the course.
// Probably prepares the object and jagged shadow models and records their data blocks.
// The second model is skipped for race configuration type six.

typedef struct ModelData {
    int unused_00;
    unsigned char *resource;
} ModelData;

extern char data_0216c21c[];
extern char data_0216c230[];
extern ModelData *data_0217b80c;
extern void *data_0217b810;
extern void *data_0217b814;
extern void *data_0217b818;
extern int *gRaceConfig;

extern void *FormatFindMapObjFileBuffer_0_from_thumb(void *name);
extern void func_020ea588(ModelData **out_model, void *nsbmd, int flag);
extern void Model_Render(void *model, int mode);
extern void StructML_SomeFn_8(void *model, int value);
extern void *find_buf_fn_from_thumb(char *name);
extern void func_020ea55c(void **out_model, void *nsbmd, int mode);

void func_020e52bc(void)
{
    ModelData *model;
    unsigned char *block1;
    unsigned char *block2;
    void *file_buffer;

    file_buffer = FormatFindMapObjFileBuffer_0_from_thumb(data_0216c21c);
    func_020ea588(&data_0217b80c, file_buffer, 0);
    Model_Render(data_0217b80c, 0x3f);
    StructML_SomeFn_8(data_0217b80c, 0);

    model = data_0217b80c;
    block1 = model->resource;
    block1 += *(int *)(block1 + 8);
    block1 += *(int *)(block1 + *(unsigned short *)(block1 + 10) + 8);
    data_0217b814 = block1;
    block2 = model->resource;
    block2 += *(int *)(block2 + 12);
    block2 += *(int *)(block2 + *(unsigned short *)(block2 + 6) + 4);
    data_0217b818 = block2;

    if (gRaceConfig[3] != 6) {
        func_020ea55c(&data_0217b810, find_buf_fn_from_thumb(data_0216c230), 0x3f);
    }
}
