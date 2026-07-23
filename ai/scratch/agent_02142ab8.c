// PURPOSE: Queues a wireless command for the ARM7 processor.
// The first argument is the command identifier and the second is the number
// of following word arguments. It probably reuses a shared 256-byte command
// buffer and returns 2 when queued or 8 when no buffer can be sent.

typedef unsigned int u32;
typedef unsigned short u16;
typedef char *va_list;

#define va_start(ap, last) \
    ((ap) = (char *)((((u32)&(last)) & ~3) + 4))
#define va_arg(ap, type) \
    (*(type *)(((ap) += sizeof(type)) - sizeof(type)))

typedef struct WmWork {
    void *buffer1;
    void *buffer2;
    u32 unknown_08;
    void *commandBuffer;
    void *buffer3;
    u16 dmaChannel;
} WmWork;

extern WmWork *data_0217eed4;
extern unsigned char data_0217eed8[];

extern int Os_ReceiveMessage(void *queue, void **message, int flags);
extern int OS_JamMessage(void *queue, void *message, int flags);
extern int Os_MessageQueue_Send(void *queue, void *message, int flags);
extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern void DC_SomeClean(void *start, u32 length);
extern void MI_DmaCopy32(u32 channel, const void *source, void *destination,
                         u32 length);
extern int Fifo_SendWord(u32 channel, u32 word, int async);

int WM_SomeFn(u16 command, u16 count, ...)
{
    void *message;
    va_list arguments;
    int i;
    int fifoResult;

    if (Os_ReceiveMessage(data_0217eed8, &message, 0) == 0) {
        return 8;
    }

    DC_InvalidateRangeNoClean(message, 2);
    if ((*(u16 *)message & 0x8000) == 0) {
        OS_JamMessage(data_0217eed8, message, 1);
        return 8;
    }

    if (count == 0) {
        DC_SomeClean(data_0217eed4->commandBuffer, 0x100);
        DC_InvalidateRangeNoClean(message, 0x100);
        MI_DmaCopy32(data_0217eed4->dmaChannel,
                     data_0217eed4->commandBuffer, message, 0x100);
    }

    *(u16 *)message = command;
    va_start(arguments, count);
    for (i = 0; i < count; i++) {
        ((u32 *)message)[i + 1] = va_arg(arguments, u32);
    }

    DC_SomeClean(message, 0x100);
    fifoResult = Fifo_SendWord(10, (u32)message, 0);
    Os_MessageQueue_Send(data_0217eed8, message, 1);

    return fifoResult < 0 ? 8 : 2;
}
