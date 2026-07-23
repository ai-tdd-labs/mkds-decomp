/* PURPOSE: Sends the sound command request until the sound system accepts it.
 * This function probably starts a request on FIFO channel seven.
 * It sends a zero command word with synchronous delivery disabled.
 * A negative result means the request is retried.
 */

typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);

void SoundInternal_RequestCommandProc(void)
{
    while (Fifo_SendWord(7, 0, 0) < 0) {
        /* Retry while the FIFO reports a temporary failure. */
    }
}
