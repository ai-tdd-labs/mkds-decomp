// PURPOSE: Ensures the game card is enabled before continuing.
// Arguments: none.
// Behavior: Stops the system when the card is not enabled.

extern int Card_IsEnabled(void);
extern void Os_Terminate(void);

void EnsureCardEnabled(void) {
    if (Card_IsEnabled()) {
        return;
    }
    Os_Terminate();
}
