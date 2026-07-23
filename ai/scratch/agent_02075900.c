// PURPOSE: Updates a high-detail camera object for its current state.
// The state selects a camera update path and supplies its position data.
// Race mode 5 probably follows a specific driver with a stored height offset.
// The final pair of values is blended toward the state's target pair.

typedef signed short s16;
typedef unsigned short u16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct StructHDState {
    VecFx32 position;
    char pad_00c[0x1c - 0x0c];
    int yOffset;
    char pad_020[0x2c - 0x20];
    int driverIndex;
    char pad_030[0x32 - 0x30];
    s16 startX;
    s16 startY;
    char pad_036[0x38 - 0x36];
    s16 endX;
    s16 endY;
    s16 blendStep;
    u16 state;
} StructHDState;

typedef struct StructHD {
    char pad_000[0x18];
    VecFx32 target;
    VecFx32 position;
    char pad_030[0x68 - 0x30];
    s16 blendX;
    s16 blendY;
    char pad_06c[0x210 - 0x6c];
    u16 driverIndex;
    char pad_212[0x218 - 0x212];
    StructHDState *state;
    char pad_21c[0x240 - 0x21c];
    int blendProgress;
} StructHD;

typedef struct RaceConfig {
    char pad_000[0x0c];
    int mode;
} RaceConfig;

extern RaceConfig *gRaceConfig;

extern void GetDriverMaybeSfxPosition(void *position, u16 index);
extern void StructHD_SomeFn_3(StructHD *obj);
extern void StructHD_SomeFn_8(StructHD *obj);
extern void StructHD_SomeFn_9(StructHD *obj);
extern void StructHD_SomeFn_10(StructHD *obj);
extern void StructHD_SomeFn_12(StructHD *obj);
extern void StructHD_SomeLookAt(StructHD *obj);

void StructHD_SomeFn_1(StructHD *obj)
{
    switch (obj->state->state) {
    case 0:
        obj->position = obj->state->position;

        if (gRaceConfig->mode == 5) {
            obj->driverIndex = (obj->state->driverIndex >> 12) - 1;
            GetDriverMaybeSfxPosition(&obj->target, obj->driverIndex);
            obj->target.y += obj->state->yOffset;
        } else {
            GetDriverMaybeSfxPosition(&obj->target, obj->driverIndex);
            obj->target.y += 0x6000;
        }

        StructHD_SomeLookAt(obj);
        break;

    case 1:
        StructHD_SomeFn_3(obj);
        break;

    case 2:
        obj->position = obj->state->position;
        StructHD_SomeFn_8(obj);
        StructHD_SomeFn_10(obj);
        break;

    case 3:
        StructHD_SomeFn_9(obj);
        break;

    case 4:
        break;

    case 5:
    case 6:
        StructHD_SomeFn_12(obj);
        break;
    }

    {
        StructHDState *state = obj->state;

        if (state->blendStep != 0) {
            int startX = state->startX;
            int endX = state->endX;
            int startY = state->startY;
            int endY = state->endY;
            int progress = obj->blendProgress;
            int deltaX = endX - startX;
            int deltaY = endY - startY;

            obj->blendX =
                startX + (int)(((long long)deltaX * progress) >> 12);
            obj->blendY =
                startY + (int)(((long long)deltaY * progress) >> 12);

            obj->blendProgress += state->blendStep;
            if (obj->blendProgress > 0x1000) {
                obj->blendProgress = 0x1000;
            }
            return;
        }

        obj->blendX = state->startX;
        obj->blendY = state->startY;
    }
}
