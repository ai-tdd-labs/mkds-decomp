// PURPOSE: Sets up the shared display configuration for this screen.
// It copies the shared display settings before creating the configuration.
// The resulting configuration probably enables the two background layers used here.

typedef unsigned short u16;

extern u16 data_0216e354[];

extern void *CreateDisplayConfig(void *heap, u16 *settings);
extern void DisplayEngineConfig_SetBg1Config(void *config, int a1, int a2,
                                              int a3, int a4, int a5, int a6,
                                              int a7);
extern void DisplayEngineConfig_SetBg3Config(void *config, int a1, int a2,
                                              int a3, int a4, int a5, int a6);
extern void SetGlobalDisplayConfig(void *config);

void *func_02125028(void *heap)
{
    u16 settings[20];
    u16 *src;
    u16 *dst;
    int count;
    void *config;

    src = data_0216e354;
    dst = settings;
    count = 20;
copy_settings:
        *dst++ = *src++;
        count--;
    if ((unsigned int)count != 0)
        goto copy_settings;

    config = CreateDisplayConfig(heap, settings);
    DisplayEngineConfig_SetBg1Config((char *)config + 0x28, 0, 0, 0, 0, 0x12, 2, 0);
    DisplayEngineConfig_SetBg3Config((char *)config + 0x70, 1, 0, 0, 0, 0xf, 0);
    SetGlobalDisplayConfig(config);
    *(volatile unsigned int *)0x04000000 =
        (*(volatile unsigned int *)0x04000000 & 0xffcfffef) | 0x10;
    *(volatile unsigned int *)0x04001000 =
        (*(volatile unsigned int *)0x04001000 & 0xffcfffef) | 0x10;
    return config;
}
