// PURPOSE: Updates the navigation screen contexts during vertical blank.
// This function takes no arguments.
// It probably gives each active navigation context its VBlank update.

typedef struct BackScreen {
    void *textSystemContext;
    void *selectChoisesContext;
    void *selectReturnContext;
} BackScreen;

extern BackScreen *data_0217d3ec;

extern void TextSystemContext_OnSceneVblank_from_thumb(void *context);
extern void SelectChoisesContext_OnSceneVblank_from_thumb(void *context);
extern void SelectReturnContext_OnSceneVblank_from_thumb(void *context);

void NavigationContext_OnSceneVblank_from_thumb(void)
{
    if (data_0217d3ec->textSystemContext != 0) {
        TextSystemContext_OnSceneVblank_from_thumb(data_0217d3ec->textSystemContext);
    }

    if (data_0217d3ec->selectChoisesContext != 0) {
        SelectChoisesContext_OnSceneVblank_from_thumb(data_0217d3ec->selectChoisesContext);
    }

    if (data_0217d3ec->selectReturnContext != 0) {
        SelectReturnContext_OnSceneVblank_from_thumb(data_0217d3ec->selectReturnContext);
    }
}
