/* PURPOSE: Registers the sound FIFO handler and waits for it to become ready.
 * Takes no arguments and returns no value.
 * It only waits for the ARM7-side handler when sound commands are available.
 */

typedef void (*FifoHandler)(unsigned int tag, unsigned int data, int error);

extern void Fifo_RegisterHandler(int tag, FifoHandler handler);
extern int Sound_IsCommandAvailable(void);
extern int Fifo_IsHandlerReady(int tag, int processor);
extern void Os_SpinWait(unsigned int cycles);
extern void Sound_FifoHandler(unsigned int tag, unsigned int data, int error);

void Sound_RegisterFifoHandler(void)
{
    Fifo_RegisterHandler(7, Sound_FifoHandler);

    if (!Sound_IsCommandAvailable()) {
        return;
    }

    if (Fifo_IsHandlerReady(7, 1)) {
        return;
    }

    do {
        Os_SpinWait(100);
    } while (!Fifo_IsHandlerReady(7, 1));
}
