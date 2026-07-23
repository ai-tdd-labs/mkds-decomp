// PURPOSE: Starts an asynchronous save-data card read.
// The arguments provide the card address, destination buffer, byte count, callback,
// and probably three request settings. It refuses to start while another card task
// is active, then records the request state before submitting it.

typedef unsigned int u32;

typedef struct CardBackupWork {
    int state;
    int field_04;
    int field_08;
    int active;
    int field_10;
    int field_14;
    unsigned char unknown_18[0x10];
    void *buffer;
    int cardAddress;
    int byteCount;
    int field_34;
    int field_38;
} CardBackupWork;

extern CardBackupWork *data_021759d4;

extern int CardIsNotBusy(void);
extern int AllocateLockCardBackupResource_from_thumb(void);
extern void DC_InvalidateRangeNoClean(void *address, u32 length);
extern void func_0204b7b8(void);
extern void Card_RequestStreamCommand(
    int cardAddress, void *buffer, int byteCount, void (*callback)(void),
    void *callbackArgument, int command, int priority, int field_1c, int field_20);

int func_0204b714(int cardAddress, void *buffer, int byteCount,
                  void *callbackArgument, int field_34, int field_38, int field_14)
{
    if (data_021759d4->active == 0 || CardIsNotBusy() == 0) {
        return 0;
    }

    if (AllocateLockCardBackupResource_from_thumb() == 0) {
        return 0;
    }

    data_021759d4->field_04 = 0;
    data_021759d4->field_10 = 1;
    data_021759d4->state = 3;
    data_021759d4->cardAddress = cardAddress;
    data_021759d4->buffer = buffer;
    data_021759d4->byteCount = byteCount;
    data_021759d4->field_34 = field_38;
    data_021759d4->field_38 = field_14;
    data_021759d4->field_14 = field_34;

    DC_InvalidateRangeNoClean(buffer, byteCount);
    Card_RequestStreamCommand(cardAddress, buffer, byteCount, func_0204b7b8,
                              callbackArgument, 1, 6, 1, 0);
    return 1;
}
