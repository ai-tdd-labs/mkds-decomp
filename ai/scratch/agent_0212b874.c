typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *data_0217d410;
extern void AllocateReserveTEQSub(int command, int offset, void *source,
                                  int size);

// PURPOSE: Interpolates four tile entries and queues their graphics transfer.
void func_0212b874(int value)
{
    int i = 0;
    int outputOffset = 0;
    int inverse = 0x1000 - value;
    u8 *data = data_0217d410;
    int inputOffset = 0;

    do {
        u8 *input = data + inputOffset;
        int x = ((*(int *)(input + 0x34) * inverse) +
                 (*(int *)(input + 0x64) * value)) >> 12;
        int y = ((*(int *)(input + 0x2C) * inverse) +
                 (*(int *)(input + 0x5C) * value)) >> 12;
        int z = ((*(int *)(input + 0x30) * inverse) +
                 (*(int *)(input + 0x60) * value)) >> 12;

        *(u16 *)(data + outputOffset + 0xC) =
            (u16)((x << 10) | y | (z << 5));
        inputOffset += 0xC;
        outputOffset += 2;
        i++;
    } while (i < 4);

    data = data_0217d410;
    if (*(int *)(data + 0x8C) == 0) {
        AllocateReserveTEQSub(0x1E, data[8] << 5, data + 0xA, 0x20);
    } else {
        *(int *)(data + 0x8C) = 0;
    }
}
