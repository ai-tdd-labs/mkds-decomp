/* PURPOSE: Sends a word through FIFO channel eight until it is accepted.
 * The argument is the word sent to the FIFO.
 * This probably waits by retrying without a delay when the channel is busy.
 */

typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);

void func_0214fa7c(u32 word)
{
    while (Fifo_SendWord(8, word, 0) != 0) {
        /* Retry until the FIFO accepts the word. */
    }
}
