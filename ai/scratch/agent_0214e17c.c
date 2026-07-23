// PURPOSE: Sends a masked RTC word through the system FIFO.
/*
 * The input word is shifted into the FIFO payload field.
 * Returns whether the probably asynchronous FIFO send did not fail.
 */
typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);

int Rtc_SendFifoWord(u32 word)
{
    return Fifo_SendWord(5, (word << 8) & 0x7f00, 0) >= 0;
}
