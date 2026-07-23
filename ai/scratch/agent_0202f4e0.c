// PURPOSE: Sets the top engine's first background configuration.
// The base points to the display configuration data.
// The six integer values are forwarded to the background setup routine.
// This probably selects settings for BG1 on the top screen.
extern void DisplayEngineConfig_SetBg1Config(void *cfg, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

void DisplayConfig_SetTopEngineBg1Config_0(char *base, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    DisplayEngineConfig_SetBg1Config(base + 0x28, a1, a2, a3, a4, a5, a6, a7);
}
