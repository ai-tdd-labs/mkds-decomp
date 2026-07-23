// PURPOSE: Initializes the card subsystem state and installs its ROM access callback.
typedef struct CardWork {
    char padding_00[0x1c];
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    char padding_2c[0x0c];
    int field_38;
    int field_3c;
    char padding_40[0xd4];
    int initialized;
} CardWork;

extern CardWork data_0217fa40;
extern int data_02180060;
extern void *data_02180080;
extern void Card_InitializeContext(void);
extern void *Card_GetRomAccessFunction(void);
extern void Card_InitializePulledOutCallback(void);

void Card_Initialize(void)
{
    CardWork *state = &data_0217fa40;

    if (state->initialized != 0) {
        return;
    }

    state->initialized = 1;
    state->field_24 = 0;
    state->field_20 = state->field_24;
    state->field_1c = state->field_20;
    state->field_28 = -1;
    state->field_38 = 0;
    state->field_3c = 0;
    data_02180060 = 0;
    Card_InitializeContext();
    data_02180080 = Card_GetRomAccessFunction();
    Card_InitializePulledOutCallback();
}
