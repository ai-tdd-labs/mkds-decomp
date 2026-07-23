// PURPOSE: Finds and records the data sections inside a loaded BMG file.

extern unsigned int SwapEndianness32_from_thumb(unsigned int value);
extern void *data_0217b360;
extern void *data_0217b364;

void Bmg_Load_from_thumb(void *bmg)
{
    char *section = (char *)bmg + 0x20;
    unsigned int i;

    i = 0;
    goto loop_check;

loop_body:
    {
        char *current = section;
        unsigned int tag;

        section += *(int *)(section + 4);
        tag = SwapEndianness32_from_thumb(*(unsigned int *)current);
        if (tag != 0x44415431) {
            if (tag == 0x494e4631) {
                data_0217b360 = current;
            }
        } else {
            data_0217b364 = current;
        }
        i++;
    }

loop_check:
    if (i < *(unsigned int *)((char *)bmg + 0xc)) {
        goto loop_body;
    }
}
