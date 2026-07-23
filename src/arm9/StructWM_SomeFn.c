/* PURPOSE: Initializes wireless memory and starts its main operation.
 * Takes a wireless work buffer, a callback value, and a DMA channel.
 * It records the callback after initialization, then probably enables the
 * wireless subsystem with the three internal buffers from the global state.
 * Initialization errors pass through; a successful start is reported as 2.
 */

typedef unsigned int u32;

typedef struct StructWM {
    void *buffer1;
    void *buffer2;
    u32 unknown_08;
    void *message;
    void *buffer3;
} StructWM;

extern int Wm_Initialize(StructWM *work, u32 dmaChannel);
extern void SetSomeFunctionPtr(int slot, int callback);
extern StructWM *Wm_GetGlobal(void);
extern int WM_SomeFn(void *argument, int mode, void *buffer1, void *buffer2,
                     void *buffer3);

int StructWM_SomeFn(StructWM *work, int callback, u32 dmaChannel)
{
    int result;
    StructWM *wireless;

    result = Wm_Initialize(work, dmaChannel);
    if (result != 0) {
        return result;
    }

    SetSomeFunctionPtr(0, callback);
    wireless = Wm_GetGlobal();
    result = WM_SomeFn(0, 3, wireless->buffer1, wireless->buffer2,
                       wireless->buffer3);

    if (result == 0) {
        result = 2;
    }
    return result;
}
