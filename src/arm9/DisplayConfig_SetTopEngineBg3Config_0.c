// PURPOSE: Sets the top screen's BG3 display configuration.
// The base points to a display configuration structure.
// The remaining six values are forwarded to the BG3 configuration helper.
// This probably selects the top engine's BG3 configuration slot.

extern void DisplayEngineConfig_SetBg3Config(void *cfg, int a1, int a2, int a3, int a4, int a5, int a6);

void DisplayConfig_SetTopEngineBg3Config_0(char *base, int a1, int a2, int a3, int a4, int a5, int a6)
{
    /* Top-engine BG3 configuration is stored at offset 0x28. */
    DisplayEngineConfig_SetBg3Config(base + 0x28, a1, a2, a3, a4, a5, a6);
}
