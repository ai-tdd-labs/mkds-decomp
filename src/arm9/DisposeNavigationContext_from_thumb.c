/* PURPOSE: Frees the navigation screen contexts.
 * This function takes no arguments.
 * It disposes each existing text or selection context, then clears the
 * shared navigation context pointer.
 */

typedef struct BackScreen {
    void *textSystemContext;
    void *selectChoisesContext;
    void *selectReturnContext;
} BackScreen;

extern BackScreen *data_0217d3ec;

extern void TextSystemContext_Dispose_from_thumb(void *context);
extern void SelectChoisesContext_Dispose_from_thumb(void *context);
extern void SelectReturnContext_Dispose_from_thumb(void *context);

void DisposeNavigationContext_from_thumb(void)
{
    if (data_0217d3ec->textSystemContext != 0) {
        TextSystemContext_Dispose_from_thumb(data_0217d3ec->textSystemContext);
    }

    if (data_0217d3ec->selectChoisesContext != 0) {
        SelectChoisesContext_Dispose_from_thumb(data_0217d3ec->selectChoisesContext);
    }

    if (data_0217d3ec->selectReturnContext != 0) {
        SelectReturnContext_Dispose_from_thumb(data_0217d3ec->selectReturnContext);
    }

    data_0217d3ec = 0;
}
