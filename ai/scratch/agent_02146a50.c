/* PURPOSE: Sends a card command through the system FIFO.
 * The first argument is the command word and the second is the delay between
 * retries. It tries channel 14 immediately, then waits and retries until the
 * FIFO accepts the word. */

typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);
extern void WaitByLoop(u32 delay);

void Card_SendToFifo(u32 commandWord, u32 retryDelay)
{
    if (Fifo_SendWord(0xe, commandWord, 0) == 0) {
        return;
    }

    do {
        WaitByLoop(retryDelay);
    } while (Fifo_SendWord(0xe, commandWord, 0) != 0);
}
