// PURPOSE: Loads and prepares the course traffic models.
// The argument receives whether traffic is enabled and has its state cleared.
// This loads the car, truck, bus, tire, shadow, and texture-animation resources.
// It also probably copies model values into every active traffic object.

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RaceConfig {
    int field_00;
    int field_04;
    int mode;
    u8 padding_0c[0x62 - 0x0c];
    s8 racer_index;
} RaceConfig;

typedef struct TrafficSetup {
    u8 padding_00[0x38];
    int enabled;
    int state;
} TrafficSetup;

typedef struct ModelBlock {
    u8 padding_00[0x18];
    u8 material_count;
} ModelBlock;

typedef struct Model {
    int field_00;
    ModelBlock *block;
} Model;

typedef struct TrafficValueSource {
    u8 padding_00[0x20];
    int *value_20;
    int *value_24;
    int *value_28;
} TrafficValueSource;

typedef struct TrafficObject {
    u8 padding_000[0x124];
    int value_124;
    int value_128;
    int value_12c;
    u8 padding_130[0x154 - 0x130];
    TrafficValueSource *value_source;
} TrafficObject;

typedef struct TrafficObjectList {
    TrafficObject **objects;
    u16 count;
} TrafficObjectList;

extern char data_0216c054[];
extern char data_0216c060[];
extern char data_0216c070[];
extern char data_0216c07c[];
extern char data_0216c08c[];
extern char data_0216c0a0[];
extern char data_0216c0b8[];
extern char data_0216c0cc[];
extern char data_0216c0d8[];

extern RaceConfig *gRaceConfig;
extern Model *data_0217b7a0;
extern Model *data_0217b794;
extern Model *data_0217b7ac;
extern Model *data_0217b790;
extern void *data_0217b788;
extern void *data_0217b798;
extern void *data_0217b7b0;
extern void *data_0217b78c;
extern void *data_0217b7a8;
extern TrafficObjectList *data_0217b79c;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern int func_0203c5e4(void);
extern void func_020ea588(Model **destination, void *model_data, int flag);
extern void func_020ea55c(void **destination, void *model_data, int flag);
extern void func_020ea4bc(int type, Model *model, void **animation,
                         void *model_data, void *animation_data);
extern void Model_SetPolygonIdLightFlagsEmi(Model *model, int polygon_id,
                                             int light_flags, int emission);
extern void ModelBlock_SomeTexPltFn_3(ModelBlock *model, u32 material_index,
                                      int polygon_id);
extern void StructML_SomeFn_8(Model *model, int value);

void func_020e20a8(TrafficSetup *setup)
{
    void *car_model_data;
    void *truck_model_data;
    ModelBlock *model_block;
    u32 material_index;
    int object_index;
    u16 object_count;

    car_model_data =
        FormatFindMapObjFileBuffer_from_thumb(data_0216c054);
    truck_model_data =
        FormatFindMapObjFileBuffer_from_thumb(data_0216c060);

    setup->enabled =
        gRaceConfig->mode != 4 &&
        func_0203c5e4() == 0 &&
        (u16)gRaceConfig->racer_index < 8;
    setup->state = 0;

    func_020ea588(&data_0217b7a0, car_model_data, 0);
    func_020ea588(&data_0217b794, truck_model_data, 0);
    func_020ea588(
        &data_0217b7ac,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c070), 0);
    func_020ea588(
        &data_0217b790,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c07c), 0);

    func_020ea55c(
        &data_0217b788,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c08c), 7);
    func_020ea55c(
        &data_0217b798,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c0a0), 7);
    func_020ea55c(
        &data_0217b7b0,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c0b8), 7);

    func_020ea4bc(
        2, data_0217b7a0, &data_0217b78c, car_model_data,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c0cc));
    func_020ea4bc(
        2, data_0217b794, &data_0217b7a8, truck_model_data,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c0d8));

    Model_SetPolygonIdLightFlagsEmi(data_0217b7a0, 0x3f, 2, 0x294a);
    material_index = 0;
    model_block = data_0217b7a0->block;
    if (material_index < model_block->material_count) {
        do {
            ModelBlock_SomeTexPltFn_3(model_block, material_index, 7);
            material_index++;
        } while (material_index < model_block->material_count);
    }

    Model_SetPolygonIdLightFlagsEmi(data_0217b794, 0x3f, 2, 0x294a);
    material_index = 0;
    model_block = data_0217b794->block;
    if (material_index < model_block->material_count) {
        do {
            ModelBlock_SomeTexPltFn_3(model_block, material_index, 7);
            material_index++;
        } while (material_index < model_block->material_count);
    }

    Model_SetPolygonIdLightFlagsEmi(data_0217b7ac, 0x3f, 2, 0x294a);
    material_index = 0;
    model_block = data_0217b7ac->block;
    if (material_index < model_block->material_count) {
        do {
            ModelBlock_SomeTexPltFn_3(model_block, material_index, 7);
            material_index++;
        } while (material_index < model_block->material_count);
    }

    Model_SetPolygonIdLightFlagsEmi(data_0217b790, 0x3f, 2, 0x294a);
    material_index = 0;
    model_block = data_0217b790->block;
    if (material_index < model_block->material_count) {
        do {
            ModelBlock_SomeTexPltFn_3(model_block, material_index, 7);
            material_index++;
        } while (material_index < model_block->material_count);
    }
    StructML_SomeFn_8(data_0217b790, 0);

    object_count = data_0217b79c->count;
    for (object_index = 0; object_index < object_count; object_index++) {
        TrafficObject *object = data_0217b79c->objects[object_index];

        object->value_124 =
            object->value_source->value_20 == 0
                ? 0
                : *object->value_source->value_20;
        object->value_128 =
            object->value_source->value_24 == 0
                ? 0
                : *object->value_source->value_24;
        object->value_12c =
            object->value_source->value_28 == 0
                ? 0
                : *object->value_source->value_28;
    }
}
