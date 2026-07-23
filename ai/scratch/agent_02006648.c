// PURPOSE: Writes a small data record into an output buffer.
extern void Mem_CpuCopy8(const void *source, void *destination, unsigned int size);
extern void Mem_CpuFill8(void *destination, unsigned int value, unsigned int size);

int func_02006648(void *output, unsigned short value, unsigned char flag,
                  unsigned int word0, unsigned int word1,
                  const void *payload, unsigned int payloadSize)
{
    struct {
        unsigned char kind;
        unsigned char padding;
        unsigned short value;
    } header;
    unsigned char *cursor;

    header.value = value;
    header.kind = 7;

    Mem_CpuCopy8(&header.kind, output, 1);
    cursor = (unsigned char *)output + 1;
    Mem_CpuCopy8(&header.value, cursor, 2);
    cursor += 2;
    Mem_CpuCopy8(&flag, cursor, 1);
    cursor += 1;
    Mem_CpuCopy8(&word0, cursor, 4);
    cursor += 4;
    Mem_CpuCopy8(&word1, cursor, 4);
    cursor += 4;

    if (payload == 0)
        Mem_CpuFill8(cursor, 0, payloadSize);
    else
        Mem_CpuCopy8(payload, cursor, payloadSize);

    return cursor + payloadSize - (unsigned char *)output;
}
