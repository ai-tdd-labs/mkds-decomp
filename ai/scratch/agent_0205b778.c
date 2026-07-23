// PURPOSE: Copies a newer network packet into its selected receive slot.
// The second argument selects one of four slots and contains the bytes to copy.
// Packets are accepted only in network states four and five.
// An empty slot accepts any packet; otherwise only a newer packet is copied.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NetworkState {
    u8 padding_000[0xe];
    u16 state;
} NetworkState;

typedef struct SlotFlag {
    u8 received : 1;
    u8 unknown : 7;
} SlotFlag;

extern NetworkState *data_0217aa14;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_0205b778(void *unused, u8 *packet)
{
    u32 slot = ((u32)packet[0] << 30) >> 30;
    u32 packetWord = *(u32 *)(packet + 4);
    NetworkState *network = data_0217aa14;
    u8 *source = packet + 4;
    u32 offset = slot * 0x88;
    u8 *destination = (u8 *)network + 0x104 + offset;
    u32 destinationValue = (*(u32 *)destination << 8) >> 8;
    u32 packetValue = (packetWord << 8) >> 8;
    u32 size = source[3];
    SlotFlag *flag;

    if (network->state != 4 && network->state != 5) {
        return;
    }
    if (destinationValue != 0 && destinationValue >= packetValue) {
        return;
    }

    flag = (SlotFlag *)((u8 *)network + 0x728 + offset);
    if (flag->received == 0) {
        flag->received = 1;
    }

    Mem_CpuCopy8(source, destination, size);
}
