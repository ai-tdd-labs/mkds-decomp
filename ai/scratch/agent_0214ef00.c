/* PURPOSE: Sends the system command through the FIFO.
 * The command word is probably a fixed system message.
 * Returns whether the FIFO accepted the command.
 */
typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);

int func_0214ef00(void)
{
    return Fifo_SendWord(9, 0x03004200, 0) >= 0;
}
