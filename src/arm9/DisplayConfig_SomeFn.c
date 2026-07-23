// PURPOSE: Initializes a display configuration from its setup values.
// The source supplies the initial header and two probably engine-specific values.
// The destination's engine blocks are cleared and its runtime fields are reset.

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    u16 values[20];
} DisplayConfigHeader;

typedef struct {
    DisplayConfigHeader header;
    u8 engine_a[0x44];
    u32 field_6c;
    u8 engine_b[0x44];
    u32 field_b4;
    u32 field_b8;
    u32 field_bc;
    u32 field_c0;
    u32 field_c4;
    u32 field_c8;
    u32 field_cc;
    u32 field_d0;
    u32 field_d4;
    u8 field_d8;
} DisplayConfig;

extern void DisplayEngineConfig_SomeClearFn(void *config, u16 value);

void DisplayConfig_SomeFn(DisplayConfig *config, const DisplayConfigHeader *setup)
{
    config->header = *setup;
    DisplayEngineConfig_SomeClearFn(config->engine_a, setup->values[4]);
    DisplayEngineConfig_SomeClearFn(config->engine_b, setup->values[6]);
    config->field_6c = 0;
    config->field_bc = 0;
    config->field_c0 = 0;
    config->field_c4 = 0;
    config->field_c8 = 0;
    config->field_cc = 0;
    config->field_d0 = 0;
    config->field_d4 = 0;
    config->field_b4 = 0;
    config->field_b8 = 0;
    config->field_d8 = 0;
}
