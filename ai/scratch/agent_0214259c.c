// PURPOSE: Returns the wireless manager's current status value.
// Checks whether the wireless manager has already initialized.
// Returns zero when it has, or probably returns a saved status value otherwise.

extern int Wm_CheckInitialized(void);
extern int *data_0217eed4;

int func_0214259c(void) {
    return Wm_CheckInitialized() ? 0 : data_0217eed4[1];
}
