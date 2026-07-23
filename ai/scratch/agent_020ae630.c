typedef unsigned int u32;

typedef struct OamBuffer {
    unsigned char entries[0x400];
    unsigned short used_count;
} OamBuffer;

extern void Arm_FlushRange(void *buffer, u32 size);

void OamBuffer_SomeFn2_from_thumb(OamBuffer *main_buffer, OamBuffer *sub_buffer)
{
    // PURPOSE: Hides every unused sprite entry in both OAM buffers.
    u32 value;
    int count;
    int i;
    int j;

    if (main_buffer != 0) {
        count = main_buffer->used_count;
        Arm_FlushRange(main_buffer, 0x400);

        i = 0;
        goto main_check;
main_loop:
        value = *(u32 *)&main_buffer->entries[(count + i) * 8];
        value = (value & 0xFFFFFE00) | 0x01800000;
        *(u32 *)&main_buffer->entries[(count + i) * 8] = value;
        main_buffer->entries[(count + i) * 8] = 0xE0;
        i++;
main_check:
        if (i < 0x80 - count)
            goto main_loop;
    }

    if (sub_buffer != 0) {
        count = sub_buffer->used_count;
        Arm_FlushRange(sub_buffer, 0x400);

        j = 0;
        goto sub_check;
sub_loop:
        value = *(u32 *)&sub_buffer->entries[(count + j) * 8];
        value = (value & 0xFFFFFE00) | 0x01800000;
        *(u32 *)&sub_buffer->entries[(count + j) * 8] = value;
        sub_buffer->entries[(count + j) * 8] = 0xE0;
        j++;
sub_check:
        if (j < 0x80 - count)
            goto sub_loop;
    }
}
