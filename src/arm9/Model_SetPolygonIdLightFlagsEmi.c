// PURPOSE: Sets a model's polygon, light, and emission settings.
// The model contains its rendering block at offset 4.
// Applies the supplied polygon ID, light flags, and emission value in order.

typedef struct ModelBlock ModelBlock;

typedef struct Model {
    int unk0;
    ModelBlock *block;
} Model;

extern void ModelBlock_SetPolygonId(ModelBlock *model, int arg1);
extern void ModelBlock_SetLight(ModelBlock *model, int arg1);
extern void ModelBlock_SetEmi(ModelBlock *model, int arg1);

void Model_SetPolygonIdLightFlagsEmi(Model *model, int polygonId, int lightFlags,
                                     int emission) {
    ModelBlock_SetPolygonId(model->block, polygonId);
    ModelBlock_SetLight(model->block, lightFlags);
    ModelBlock_SetEmi(model->block, emission);
}
