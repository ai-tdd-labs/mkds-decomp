// PURPOSE: Updates each active navigation screen context.
// This function takes no arguments.
// It probably advances the text and selection contexts owned by the shared
// navigation screen when they have been created.

typedef struct BackScreen {
    void *textSystemContext;
    void *selectChoisesContext;
    void *selectReturnContext;
} BackScreen;

extern BackScreen *data_0217d3ec;

extern void TextSystemContext_OnSceneUpdate_from_thumb(void *context);
extern void SelectChoisesContext_OnSceneUpdate_from_thumb(void *context);
extern void SelectReturnContext_OnSceneUpdate_from_thumb(void *context);

void NavigationContext_OnSceneUpdate_from_thumb(void)
{
    if (data_0217d3ec->textSystemContext != 0) {
        TextSystemContext_OnSceneUpdate_from_thumb(data_0217d3ec->textSystemContext);
    }

    if (data_0217d3ec->selectChoisesContext != 0) {
        SelectChoisesContext_OnSceneUpdate_from_thumb(data_0217d3ec->selectChoisesContext);
    }

    if (data_0217d3ec->selectReturnContext != 0) {
        SelectReturnContext_OnSceneUpdate_from_thumb(data_0217d3ec->selectReturnContext);
    }
}
