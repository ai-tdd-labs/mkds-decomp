// PURPOSE: Configures background 1 for the bottom display engine.
// Passes the bottom engine configuration block and six settings onward.
// The configuration block begins 0x70 bytes into the supplied base pointer.
// This probably mirrors the equivalent background 3 configuration wrapper.

extern void DisplayEngineConfig_SetBg1Config(void *cfg, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

void DisplayConfig_SetBottomEngineBg1Config(char *base, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    DisplayEngineConfig_SetBg1Config(base + 0x70, a1, a2, a3, a4, a5, a6, a7);
}
