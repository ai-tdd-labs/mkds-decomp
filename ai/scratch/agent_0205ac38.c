// PURPOSE: Packs temporary records into a compact transfer buffer.
// The function writes sixteen one-byte descriptors followed by up to 48 payload bytes.
// Only active records with nonempty payloads that still fit are copied.
// It stores the unused payload capacity back in the global work area.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TemporaryRecord {
    void *unknown_00;
    const void *payload;
    u8 state;
    u8 low_value;
    u8 high_value;
    u8 payload_size;
} TemporaryRecord;

typedef struct TransferBuffer {
    u8 padding_00[0x28];
    u8 descriptors[16];
    u8 payload[0x30];
} TransferBuffer;

typedef struct TransferBufferHolder {
    u8 padding_00[4];
    TransferBuffer buffer;
} TransferBufferHolder;

typedef struct TemporaryRecordWork {
    u8 padding_000[0x324];
    TemporaryRecord records[16];
    u8 padding_3e4[0x340];
    u16 remaining_capacity;
    u8 padding_726[0x2e];
    TransferBufferHolder *transfer;
} TemporaryRecordWork;

extern TemporaryRecordWork *data_0217aa14;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_0205ac38(void)
{
    u16 index;
    u8 *descriptor;
    u8 *payload;
    u16 used = 0;
    TransferBuffer *buffer =
        (TransferBuffer *)((int)data_0217aa14->transfer + 4);

    descriptor = buffer->descriptors;
    payload = descriptor + 16;

    for (index = 0; index < 16; index++) {
        TemporaryRecord *record = &data_0217aa14->records[index];
        u8 packed;

        if (record->state == 0 || record->state == 2 ||
            record->low_value == 15) {
            packed = 15;
        } else {
            packed = (record->low_value & 0x1f) |
                     ((record->high_value << 5) & 0xe0);
        }
        *descriptor++ = packed;

        switch (record->state) {
        case 0:
            goto next_record;
        case 1:
            if (record->payload_size != 0 &&
                used + record->payload_size <= 0x30) {
                Mem_CpuCopy8(record->payload, payload,
                             record->payload_size);
                used = used + record->payload_size;
                payload += record->payload_size;
            }
            break;
        case 2:
            goto next_record;
        }

next_record:
        ;
    }

    data_0217aa14->remaining_capacity = 0x30 - used;
}
