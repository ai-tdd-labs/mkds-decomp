// PURPOSE: Starts the sound system once.
// It probably prepares the shared sound lock and internal command state.
// Later calls leave the already initialized system unchanged.

extern int data_021732ac;
extern int data_021732b0;
extern void Os_Mutex_Initialize(void *mutex);
extern void Sound_InitializeCommands(void);
extern void Sound_InitializeAlarms(void);

void Sound_InitializeImpl(void) {
    if (data_021732ac != 0) {
        return;
    }

    data_021732ac = 1;
    Os_Mutex_Initialize(&data_021732b0);
    Sound_InitializeCommands();
    Sound_InitializeAlarms();
}
