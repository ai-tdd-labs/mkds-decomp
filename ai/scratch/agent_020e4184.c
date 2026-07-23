// PURPOSE: Loads the models needed by the rotary-room map objects.

typedef unsigned short u16;

typedef struct MapObjectList {
    void **objects;
    u16 count;
} MapObjectList;

extern char data_0216c188[];
extern char data_0216c19c[];
extern char data_0216c1b0[];
extern char data_0216c1c4[];
extern char data_0216c1d8[];

extern void *data_0217b7e8;
extern void *data_0217b7d8;
extern void *data_0217b7d4;
extern void *data_0217b7ec;
extern void *data_0217b7e0;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *destination, void *modelFile, int index);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                            int lightFlags, int emission);

void func_020e4184(MapObjectList *list)
{
    int j;
    int i;
    int index;
    int count;
    int loaded[5];

    for (j = 0; j < 5; j++) {
        loaded[j] = 0;
    }

    count = list->count;
    if (count > 0) {
        i = 0;
        index = 0;
        do {
            void *object = list->objects[i];
            int type = *(int *)((char *)object + 0x158);

            if (loaded[type] == 0) {
                switch (type) {
                case 0:
                    func_020ea588(&data_0217b7e8,
                                  FormatFindMapObjFileBuffer_from_thumb(data_0216c188),
                                  index);
                    Model_SetPolygonIdLightFlagsEmi(data_0217b7e8, 0x3f, 2, 0x294a);
                    break;
                case 1:
                    func_020ea588(&data_0217b7d8,
                                  FormatFindMapObjFileBuffer_from_thumb(data_0216c19c),
                                  index);
                    Model_SetPolygonIdLightFlagsEmi(data_0217b7d8, 0x3f, 2, 0x294a);
                    break;
                case 2:
                    func_020ea588(&data_0217b7d4,
                                  FormatFindMapObjFileBuffer_from_thumb(data_0216c1b0),
                                  index);
                    Model_SetPolygonIdLightFlagsEmi(data_0217b7d4, 0x3f, 2, 0x294a);
                    break;
                case 3:
                    func_020ea588(&data_0217b7ec,
                                  FormatFindMapObjFileBuffer_from_thumb(data_0216c1c4),
                                  index);
                    Model_SetPolygonIdLightFlagsEmi(data_0217b7ec, 0x3f, 2, 0x294a);
                    break;
                case 4:
                    func_020ea588(&data_0217b7e0,
                                  FormatFindMapObjFileBuffer_from_thumb(data_0216c1d8),
                                  index);
                    Model_SetPolygonIdLightFlagsEmi(data_0217b7e0, 0x3f, 2, 0x294a);
                    break;
                }
                loaded[type] = 1;
            }
            i++;
        } while (i < count);
    }

    for (i = 0; i < list->count; i++) {
        void *object = *(void **)((char *)list->objects + i * 4);

        switch (*(int *)((char *)object + 0x158)) {
        case 0:
            *(void **)((char *)object + 0x140) = data_0217b7e8;
            break;
        case 1:
            *(void **)((char *)object + 0x140) = data_0217b7d8;
            break;
        case 2:
            *(void **)((char *)object + 0x140) = data_0217b7d4;
            break;
        case 3:
            *(void **)((char *)object + 0x140) = data_0217b7ec;
            break;
        case 4:
            *(void **)((char *)object + 0x140) = data_0217b7e0;
            break;
        }
    }
}
