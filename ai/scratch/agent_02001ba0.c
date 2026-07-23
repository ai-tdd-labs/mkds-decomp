// PURPOSE: Sets up the logo screen and its navigation system.
// The argument is the heap used for the logo context and display configuration.
// This loads graphics for both screens and creates the logo state handler.
// It also opens the probably shared message file and prepares navigation resources.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct LogoScreenGraphics {
    void *palette;
    void *characters;
    void *screen;
} LogoScreenGraphics;

typedef struct LogoContext {
    LogoScreenGraphics topGraphics;
    LogoScreenGraphics bottomGraphics;
    u8 stateHandler[0x14];
    u32 flags;
    u32 field_30;
    u32 field_34;
    void *messageFile;
} LogoContext;

typedef struct NavigationContextConfig {
    int enabled;
    void *font;
    int field_08;
    int field_0c;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
} NavigationContextConfig;

typedef struct DisplayConfig DisplayConfig;

extern char data_021547c8[];

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern DisplayConfig *CreateDisplayConfig(void *heap, char *templateData);
extern void DisplayEngineConfig_SetBg1Config(
    void *config, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern void SetGlobalDisplayConfig(DisplayConfig *config);
extern void LoadLogoScreenGraphics(
    LogoScreenGraphics *graphics, int topScreen, void *palettePath,
    void *characterPath, void *screenPath);
extern void StateDualHandler_Create(
    void *handler, const void *stateTable, int stateCount, void *owner);
extern void *
FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void *GetLoadedFont_from_thumb(int fontType);
extern void PrepareNavigationContextFiles_from_thumb(void);
extern void InitializeNavigationContext_from_thumb(
    void *heap, NavigationContextConfig *config);

#define LOGO_CONTEXT (*(LogoContext **)0x021a99e0)

void InitializeLogoContext(void *heap)
{
    DisplayConfig *displayConfig;
    NavigationContextConfig navigationConfig;

    LOGO_CONTEXT = Mem_AllocateHeap(heap, 0x3c);

    displayConfig = CreateDisplayConfig(heap, data_021547c8);
    DisplayEngineConfig_SetBg1Config(
        (char *)displayConfig + 0x28, 1, 0, 0, 0, 0, 1, 0);
    DisplayEngineConfig_SetBg1Config(
        (char *)displayConfig + 0x70, 1, 0, 0, 0, 0, 2, 0);
    SetGlobalDisplayConfig(displayConfig);

    LoadLogoScreenGraphics(
        &LOGO_CONTEXT->topGraphics, 1, (void *)0x021a76ac,
        (void *)0x021a76c8, (void *)0x021a76e4);
    LoadLogoScreenGraphics(
        &LOGO_CONTEXT->bottomGraphics, 0, (void *)0x021a76fc,
        (void *)0x021a7718, (void *)0x021a7734);

    StateDualHandler_Create(
        LOGO_CONTEXT->stateHandler, (const void *)0x02001080, 0xc, 0);

    LOGO_CONTEXT->flags &= ~1u;
    LOGO_CONTEXT->field_30 = 0;
    LOGO_CONTEXT->messageFile =
        FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(
            (char *)0x021a7750);

    navigationConfig.enabled = 1;
    navigationConfig.font = GetLoadedFont_from_thumb(1);
    navigationConfig.field_08 = 0;
    navigationConfig.field_0c = 1;
    navigationConfig.field_10 = 0;
    navigationConfig.field_14 = 0;
    navigationConfig.field_18 = 0;
    navigationConfig.field_1c = 0;
    navigationConfig.field_20 = 0;
    navigationConfig.field_24 = 0;

    PrepareNavigationContextFiles_from_thumb();
    InitializeNavigationContext_from_thumb(heap, &navigationConfig);
}
