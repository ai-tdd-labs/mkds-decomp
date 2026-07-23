// PURPOSE: Initializes the shared race state for every racer slot.
// This allocates the eight-slot race work table and fills its default fields.
// Active slots derive a small type value from the race configuration.
// Unused slots are marked inactive, and the shared status starts at -1.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceConfigRacer {
    int type;
    u8 pad_04[0x2c];
} RaceConfigRacer;

typedef struct RaceConfig {
    u8 pad_000[0x74];
    RaceConfigRacer racers[8];
    u8 pad_1f4[0x3d0 - 0x1f4];
    u8 racerCount;
} RaceConfig;

typedef struct RacerRaceState {
    u8 pad_00[0x08];
    int state;
    u8 pad_0c[0x18 - 0x0c];
    int field_18;
    int field_1c;
    u8 pad_20[0x44 - 0x20];
    u16 racerId;
    u16 racerType;
    u16 field_48;
    u8 pad_4a[0x4c - 0x4a];
    int field_4c;
    u16 field_50;
    u8 pad_52[0x70 - 0x52];
} RacerRaceState;

typedef struct RaceState {
    RacerRaceState racers[8];
    u8 pad_380[0x3b4 - 0x380];
    int status;
    u8 pad_3b8[0x3c0 - 0x3b8];
} RaceState;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern RaceState *data_0217b1fc;
extern RaceConfig *gRaceConfig;

void func_020a0e00(void)
{
    int i;

    data_0217b1fc = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x3c0);

    for (i = 0; i < 8; i++) {
        u16 racer = (u16)i;
        RacerRaceState *state = &data_0217b1fc->racers[i];

        state->field_1c = -2;
        state->field_18 = -2;
        state->racerId = racer;
        state->field_48 = racer;

        if (i < gRaceConfig->racerCount) {
            switch (gRaceConfig->racers[racer].type) {
            case 0:
                state->racerType = 1;
                break;
            case 1:
                state->racerType = 3;
                break;
            default:
                state->racerType = racer;
                break;
            }

            state->state = 0;
            state->field_4c = 0;
            state->field_50 = 0;
        } else {
            state->state = 2;
            state->field_4c = -1;
            state->field_50 = 0;
            state->racerType = gRaceConfig->racerCount;
        }
    }

    data_0217b1fc->status = -1;
}
