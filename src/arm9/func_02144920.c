// PURPOSE: Queues a valid wireless shared-data packet for later processing.
// The callback provides the packet, its size, its sequence number, and the queue context.
// Accepted packets are copied into one of four slots and advance the write cursor.
// An unsuccessful callback probably marks the sharing session as stopped.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *buffer1;
    void *buffer2;
} WmGlobal;

typedef struct {
    u16 aidBitmap;
    u16 receivedBitmap;
    u16 data[0xfe];
} WMDataSet;

typedef struct {
    WMDataSet dataSets[4];
    u16 sequenceNumbers[4];
    u16 writeIndex;
    u16 sendIndex;
    u16 readIndex;
    u16 aidBitmap;
    u16 dataLength;
    u16 stationCount;
    u16 dataSetLength;
    u16 port;
    u16 doubleMode;
    u16 currentSequenceNumber;
    u16 state;
    u16 reserved;
} WMDataSharingInfo;

typedef struct {
    u16 field_00;
    u16 errorCode;
    u16 state;
    u8 pad_06[0x0c - 0x06];
    u16 *data;
    u16 length;
    u8 pad_12[0x1a - 0x12];
    u16 sequenceNumber;
    WMDataSharingInfo *info;
} WMPortRecvCallback;

extern WmGlobal *Wm_GetGlobal(void);
extern void DC_InvalidateRangeNoClean(void *start, u32 size);
extern void CopyMemory16(const void *source, void *destination, u32 size);

void func_02144920(WMPortRecvCallback *callback)
{
    WmGlobal *global;
    void *wmBuffer;
    WMDataSharingInfo *info;
    u32 packetLength;
    u16 packetBitmap;
    u16 *packet;
    u16 aid;

    global = Wm_GetGlobal();
    info = callback->info;
    wmBuffer = global->buffer2;

    if (info == 0)
        return;

    if (callback->errorCode != 0)
        goto failed;

    if (callback->state == 7)
        return;
    if (callback->state == 9)
        return;
    if (callback->state != 0x15)
        return;

    packet = callback->data;
    packetBitmap = packet[0];
    packetLength = callback->length;

    DC_InvalidateRangeNoClean((u8 *)wmBuffer + 0x184, 2);
    aid = *(u16 *)((u8 *)wmBuffer + 0x184);

    if (packetLength != info->dataSetLength) {
        if (packetLength > 0x200)
            packetLength = 0x200;
    }

    if (packetLength < 4)
        return;
    if ((packetBitmap & (1U << aid)) == 0)
        return;

    CopyMemory16(packet, &info->dataSets[info->writeIndex], packetLength);
    info->sequenceNumbers[info->writeIndex] = callback->sequenceNumber >> 1;
    info->writeIndex = (info->writeIndex + 1) & 3;
    return;

failed:
    info->state = 5;
}
