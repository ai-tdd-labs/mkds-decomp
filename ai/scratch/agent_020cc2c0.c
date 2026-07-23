// PURPOSE: Sets the top screen's second background configuration.
// Passes the configuration block inside the display config to the engine.
// The final three integer arguments are forwarded from the caller's stack.
// This probably selects settings for top-engine BG2.

extern void DisplayEngineConfig_SetBg2Config2(void *cfg, int a1, int a2, int a3,
                                               int a4, int a5, int a6);

void DisplayConfig_SetTopEngineBg2Config2(char *base, int a1, int a2, int a3,
                                          int a4, int a5, int a6)
{
    DisplayEngineConfig_SetBg2Config2(base + 0x28, a1, a2, a3, a4, a5, a6);
}
