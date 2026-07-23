// PURPOSE: Creates and installs the shared display configuration.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DisplayConfig DisplayConfig;

typedef struct DisplayConfigTemplate {
    u16 values[20];
} DisplayConfigTemplate;

extern DisplayConfigTemplate data_0216e32c;
extern volatile u32 data_04000000;
extern volatile u32 data_04001000;

extern DisplayConfig *CreateDisplayConfig(void *heap, char *template_data);
extern void DisplayEngineConfig_SetBg1Config(void *config, int a1, int a2,
                                             int a3, int a4, int a5, int a6,
                                             int a7);
extern void DisplayEngineConfig_SetBg3Config(void *config, int a1, int a2,
                                             int a3, int a4, int a5, int a6);
extern void SetGlobalDisplayConfig(DisplayConfig *config);

DisplayConfig *CreateLoadSomeDisplayConfig_from_thumb(void *heap)
{
    DisplayConfigTemplate template_data;
    DisplayConfig *config;

    template_data = data_0216e32c;
    config = CreateDisplayConfig(heap, (char *)&template_data);
    DisplayEngineConfig_SetBg1Config((char *)config + 0x28, 0, 0, 0, 0, 0x12, 2, 0);
    DisplayEngineConfig_SetBg3Config((char *)config + 0x70, 1, 0, 0, 0, 0x10, 4);
    SetGlobalDisplayConfig(config);
    data_04000000 = (data_04000000 & 0xfffffeff) | 0x10;
    data_04001000 = (data_04001000 & 0xfffffeff) | 0x10;
    return config;
}
