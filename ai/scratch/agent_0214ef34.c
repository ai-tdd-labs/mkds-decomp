// PURPOSE: Starts automatic microphone sampling through the FIFO.
// The first three arguments carry the buffer address, size, and sample interval.
// The fourth argument supplies the microphone format bits for the start command.
// Each 32-bit parameter is sent as two tagged 16-bit FIFO payloads.

typedef unsigned int u32;

extern int Fifo_SendWord(u32 channel, u32 word, int async);

int func_0214ef34(u32 bufferAddress, u32 bufferSize, u32 interval, u32 format)
{
    if (Fifo_SendWord(9, format | 0x02004100, 0) < 0) {
        return 0;
    }
    if (Fifo_SendWord(9, (bufferAddress >> 16) | 0x00010000, 0) < 0) {
        return 0;
    }
    if (Fifo_SendWord(9, (bufferAddress & 0x0000ffff) | 0x00020000, 0) < 0) {
        return 0;
    }
    if (Fifo_SendWord(9, (bufferSize >> 16) | 0x00030000, 0) < 0) {
        return 0;
    }
    if (Fifo_SendWord(9, (bufferSize & 0x0000ffff) | 0x00040000, 0) < 0) {
        return 0;
    }
    if (Fifo_SendWord(9, (interval >> 16) | 0x00050000, 0) < 0) {
        return 0;
    }

    return Fifo_SendWord(9, (interval & 0x0000ffff) | 0x01060000, 0) >= 0;
}
