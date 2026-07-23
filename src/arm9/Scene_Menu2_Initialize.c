// PURPOSE: Initializes the display settings for the second menu.
// The active execution context provides the heap for a probably predefined display setup.
// The resulting configuration enables BG1 with the menu's fixed settings and becomes global.

typedef struct DisplayConfig DisplayConfig;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern DisplayConfig *CreateDisplayConfig(void *heap, char *template_data);
extern void DisplayEngineConfig_SetBg1Config(void *config, int a1, int a2, int a3,
                                             int a4, int a5, int a6, int a7);
extern void SetGlobalDisplayConfig(DisplayConfig *config);
extern char data_02154868[];

void Scene_Menu2_Initialize(void)
{
    DisplayConfig *config;

    config = CreateDisplayConfig(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), data_02154868);
    DisplayEngineConfig_SetBg1Config((char *)config + 0x28, 0, 0, 0, 0, 4, 0, 0);
    SetGlobalDisplayConfig(config);
}
