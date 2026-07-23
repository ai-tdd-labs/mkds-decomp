// PURPOSE: Sets the top screen's background zero configuration.
// Passes the top engine's BG0 block and its seven configuration values onward.
// The base offset selects the top display engine's BG0 configuration area.

extern void DisplayEngineConfig_SetBg0Config(void *cfg, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

void DisplayConfig_SetTopEngineBg0Config(char *base, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    DisplayEngineConfig_SetBg0Config(base + 0x28, a1, a2, a3, a4, a5, a6, a7);
}
