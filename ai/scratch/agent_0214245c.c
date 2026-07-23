// PURPOSE: Reads characters into a caller-provided buffer until a line ending or its capacity is reached.

typedef unsigned int u32;

extern int Semihost_Op7(void);

int func_0214245c(int handle, char *buffer, u32 *length)
{
    u32 count = *length;
    u32 i = 0;

    if (i < count) {
        do {
            buffer[i] = (char)Semihost_Op7();
            if ((unsigned char)buffer[i] == 13) {
                *length = i + 1;
                break;
            }
            if ((unsigned char)buffer[i] == 10) {
                *length = i + 1;
                break;
            }
            i++;
        } while (i < count);
    }

    return 0;
}
