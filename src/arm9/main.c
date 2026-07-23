// PURPOSE: Starts the game's main execution after all systems are initialized.
// This boot entry point has no arguments.
// It probably hands the main execution function to the scheduler.

extern void InitializeEverything(void);
extern void SetExecuteStart(void (*function)(void));
extern void StartExecuteFunction(void);

void main(void) {
    InitializeEverything();
    SetExecuteStart(StartExecuteFunction);
}
