// PURPOSE: Sends a word through the system FIFO.
// The argument is the word to send on FIFO channel 13.
// It probably waits briefly and retries until the FIFO accepts the word.

typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);
extern void WaitByLoop(u32 delay);

void func_0200c46c(u32 word)
{
    if (Fifo_SendWord(0xd, word, 0) == 0) {
        return;
    }

    do {
        WaitByLoop(1);
    } while (Fifo_SendWord(0xd, word, 0) != 0);
}
