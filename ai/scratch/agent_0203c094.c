// PURPOSE: Initializes the title scene resources.
// Probably prepares the title scene's video configuration and files.
// It obtains the active heap before loading the title assets.

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *SomeVramConfig(void *heap);
extern void LoadTitleFiles_from_thumb(void *heap);
extern void MaybeResetInput(void);

void Scene_Title_Initialize(void) {
    LoadTitleFiles_from_thumb(SomeVramConfig(ExecutionContext_GetHeapHandle(GetActiveExecutionContext())));
    MaybeResetInput();
}
