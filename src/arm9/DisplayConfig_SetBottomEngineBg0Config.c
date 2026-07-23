/* PURPOSE: Configures background zero for the bottom display engine.
 * Passes the display configuration and six settings to the engine helper.
 * This probably selects the bottom screen's BG0 setup.
 */
extern void DisplayEngineConfig_SetBg0Config(void *cfg, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

void DisplayConfig_SetBottomEngineBg0Config(char *base, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    DisplayEngineConfig_SetBg0Config(base + 0x70, a1, a2, a3, a4, a5, a6, a7);
}
