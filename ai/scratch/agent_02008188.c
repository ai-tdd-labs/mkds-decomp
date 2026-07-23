// PURPOSE: Builds the transfer descriptor for a Nintendo DS ROM segment.
// The selector chooses the ARM9 image, ARM7 image, or the shared ROM header.
// Invalid load ranges terminate execution. ARM7 data that cannot be received
// at its load address is placed at the supplied buffer cursor instead.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RomHeader {
    u8 padding_00[0x28];
    u32 arm9_load_address;
    u32 arm9_size;
    u8 padding_30[8];
    u32 arm7_load_address;
    u32 arm7_size;
} RomHeader;

typedef struct TransferDescriptor {
    u32 receive_address;
    u32 load_address;
    u32 size;
    unsigned int is_arm7 : 1;
    unsigned int padding_flags : 31;
} TransferDescriptor;

extern void Os_Terminate(void);

void func_02008188(RomHeader *header, const int *selector,
                   TransferDescriptor *descriptor, u32 *buffer_cursor)
{
    switch (*selector) {
    case 0: {
        u32 *segment = &header->arm9_load_address;

        if (header->arm9_load_address < 0x02000000 ||
            header->arm9_load_address >= 0x022c0000 ||
            header->arm9_load_address + segment[1] > 0x022c0000) {
            Os_Terminate();
            return;
        }

        descriptor->size = segment[1];
        descriptor->load_address = segment[0];
        descriptor->receive_address = descriptor->load_address;
        descriptor->is_arm7 = 0;
        return;
    }

    case 1: {
        int invalid = 0;
        volatile int needs_receive_buffer = 0;
        u32 *segment = &header->arm7_load_address;

        if (segment[0] >= 0x02000000 && segment[0] < 0x023fe800) {
            if (segment[0] + segment[1] > 0x02300000) {
                if (segment[0] + segment[1] >= 0x023fe800 ||
                    segment[1] > 0x00040000) {
                    invalid = 1;
                } else {
                    needs_receive_buffer = 1;
                }
            }
        } else {
            if (segment[0] >= 0x037f8000 && segment[0] < 0x0380f000) {
                if (segment[0] + segment[1] <= 0x0380f000) {
                    needs_receive_buffer = 1;
                } else {
                    invalid = 1;
                }
            } else {
                invalid = 1;
            }
        }

        if (invalid == 1) {
            Os_Terminate();
        }

        descriptor->size = segment[1];
        descriptor->load_address = segment[0];
        if (needs_receive_buffer == 0) {
            descriptor->receive_address = descriptor->load_address;
        } else {
            descriptor->receive_address = *buffer_cursor;
            *buffer_cursor = *buffer_cursor + descriptor->size;
        }
        descriptor->is_arm7 = 1;
        return;
    }

    case 2:
        descriptor->size = 0x160;
        descriptor->load_address = (u32)(volatile void *)0x027ffe00;
        descriptor->receive_address = descriptor->load_address;
        descriptor->is_arm7 = 0;
        return;
    }
}
