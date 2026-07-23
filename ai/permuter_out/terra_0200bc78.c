/* PURPOSE: Starts a four-byte transfer when the transport is ready. */

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct TransferState {
    unsigned char unknown_00[0x20];
    u16 transfer_started;
} TransferState;

extern TransferState *data_0216fdec;

extern void Arm_FlushRange(void *data, u32 size);
extern void Mem_DcDrainWriteBuffer(void);
extern void func_0200bc1c(void *result);
extern int func_0200bd0c(void);
extern int func_02144048(
    void (*callback)(void *),
    void *callback_arg,
    void *data,
    u16 transfer_value,
    int destination,
    int port,
    int priority);

int func_0200bc78(u16 transfer_value, int destination, void *data)
{
    int status;

    Arm_FlushRange(data, 4);
    Mem_DcDrainWriteBuffer();

    if (func_0200bd0c() == 0) {
        return 1;
    }

    status = func_02144048(
        func_0200bc1c, 0, data, transfer_value, destination, 1, 3);

    if (status == 2) {
        data_0216fdec->transfer_started = 1;
        return 2;
    }

    return status;
}
