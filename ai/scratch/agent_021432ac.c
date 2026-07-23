// PURPOSE: Finds a received wireless packet for one child.
// The caller supplies the receive buffer and child ID.
// The child must be valid and marked ready in shared wireless state.
// Returns the matching packet record, or null if none is available.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct WmStatus {
    u8 unknown_000[0x17e];
    u16 mpReadyBitmap;
} WmStatus;

typedef struct WmGlobal {
    void *buffer1;
    WmStatus *status;
} WmGlobal;

typedef struct WmMpRecvBuffer {
    u32 unknown_00;
    u16 count;
    u16 recordLength;
    u16 unknown_08;
    u8 data[1];
} WmMpRecvBuffer;

typedef struct WmMpRecvData {
    u32 unknown_00;
    u16 aid;
} WmMpRecvData;

extern WmGlobal *Wm_GetGlobal(void);
extern int Wm_CheckInitialized(void);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);

WmMpRecvData *func_021432ac(WmMpRecvBuffer *recvBuffer, u16 aid)
{
    WmMpRecvData *records[16];
    int i;
    WmGlobal *global;

    global = Wm_GetGlobal();
    if (Wm_CheckInitialized()) {
        return 0;
    }

    if (aid < 1 || aid > 15) {
        return 0;
    }

    DC_InvalidateRangeNoClean((void *)((u32)global->status + 0x17e), 2);
    if (!(global->status->mpReadyBitmap & (1 << aid))) {
        return 0;
    }

    if (recvBuffer->count == 0) {
        return 0;
    }

    records[0] = (WmMpRecvData *)recvBuffer->data;
    i = 0;
    do {
        if (records[i]->aid == aid) {
            return records[i];
        }

        i++;
        records[i] =
            (WmMpRecvData *)((u8 *)records[i - 1] + recvBuffer->recordLength);
    } while (i < recvBuffer->count);

    return 0;
}
