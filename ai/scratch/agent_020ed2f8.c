// PURPOSE: Loads the item models used during a race.
// Builds every item model, then calls each slot's optional setup routine.
// Course 29 probably disables two rendering flags on all loaded models.

#pragma optimize_for_size on

typedef struct ItemModel {
    unsigned char pad_00[0x14];
    unsigned int flags;
} ItemModel;

typedef void (*ItemSetupCallback)(void);

typedef struct ItemSlot {
    unsigned char pad_00[0x14];
    ItemSetupCallback setupCallback;
    unsigned char pad_18[0xa8 - 0x18];
} ItemSlot;

typedef struct RaceConfig {
    int courseId;
} RaceConfig;

extern unsigned int data_0217bbfc[14];
extern ItemSlot *data_0217bc34;
extern RaceConfig *gRaceConfig;

extern char data_0216c42c[];
extern char data_0216c440[];
extern char data_0216c454[];
extern char data_0216c468[];
extern char data_0216c47c[];
extern char data_0216c48c[];
extern char data_0216c49c[];
extern char data_0216c4ac[];
extern char data_0216c4bc[];
extern char data_0216c4cc[];
extern char data_0216c4dc[];
extern char data_0216c4f0[];
extern char data_0216c504[];
extern char data_0216c518[];
extern char data_0216c52c[];
extern char data_0216c53c[];
extern char data_0216c54c[];
extern char data_0216c55c[];
extern char data_0216c56c[];
extern char data_0216c57c[];
extern char data_0216c58c[];
extern char data_0216c59c[];
extern char data_0216c5ac[];
extern char data_0216c5bc[];
extern char data_0216c5d0[];
extern char data_0216c5e4[];
extern char data_0216c5f4[];

extern ItemModel *CreateBillboardModel_from_thumb(char *modelFile,
                                                   char *patternFile,
                                                   char *textureFile);

void LoadItems_from_thumb(void)
{
    int specialCourse;
    int itemIndex;

    itemIndex = 0;
    if (itemIndex < 14) do {
        *((unsigned int *)((int)data_0217bbfc +
                          ((unsigned int)itemIndex << 2))) =
            (unsigned int)itemIndex;
    } while (++itemIndex < 14);

    ((ItemModel **)data_0217bbfc)[0] = CreateBillboardModel_from_thumb(data_0216c42c, 0, data_0216c440);
    ((ItemModel **)data_0217bbfc)[1] = CreateBillboardModel_from_thumb(data_0216c454, 0, data_0216c468);
    ((ItemModel **)data_0217bbfc)[2] = CreateBillboardModel_from_thumb(data_0216c47c, 0, data_0216c48c);
    ((ItemModel **)data_0217bbfc)[3] = CreateBillboardModel_from_thumb(data_0216c49c, 0, data_0216c4ac);
    ((ItemModel **)data_0217bbfc)[4] = CreateBillboardModel_from_thumb(data_0216c4bc, 0, data_0216c4cc);
    ((ItemModel **)data_0217bbfc)[5] = CreateBillboardModel_from_thumb(data_0216c4dc, 0, data_0216c4f0);
    ((ItemModel **)data_0217bbfc)[6] = CreateBillboardModel_from_thumb(data_0216c504, 0, data_0216c518);
    ((ItemModel **)data_0217bbfc)[7] = CreateBillboardModel_from_thumb(data_0216c52c, 0, data_0216c53c);
    ((ItemModel **)data_0217bbfc)[9] = CreateBillboardModel_from_thumb(data_0216c54c, data_0216c55c,
                                                       data_0216c56c);
    ((ItemModel **)data_0217bbfc)[10] = CreateBillboardModel_from_thumb(data_0216c57c, 0, data_0216c58c);
    ((ItemModel **)data_0217bbfc)[11] = CreateBillboardModel_from_thumb(data_0216c59c, 0, data_0216c5ac);
    ((ItemModel **)data_0217bbfc)[12] = CreateBillboardModel_from_thumb(data_0216c5bc, 0, data_0216c5d0);
    ((ItemModel **)data_0217bbfc)[13] = CreateBillboardModel_from_thumb(data_0216c5e4, 0, data_0216c5f4);
    data_0217bbfc[8] = data_0217bbfc[7];

    specialCourse = gRaceConfig->courseId == 0x1d;

    for (itemIndex = 0; itemIndex < 14; itemIndex++) {
        ItemSetupCallback setupCallback = data_0217bc34[itemIndex].setupCallback;

        if (setupCallback != 0) {
            setupCallback();
        }
        if (specialCourse != 0) {
            ((ItemModel **)data_0217bbfc)[itemIndex]->flags &= 0xffffe7ff;
        }
    }
}
