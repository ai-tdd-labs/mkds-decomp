// PURPOSE: Starts the wireless work callback and marks the request active.
// Arguments: none; it uses the shared wireless transition context.
// It probably marks two context flags before starting its embedded work object.
// If startup does not return status 2, it clears the busy flag.

typedef unsigned int u32;

typedef struct StructWM StructWM;

typedef struct WirelessContext {
    int state;
    int unk4;
    int unk8;
    int request;
    int busy;
    StructWM *work;
} WirelessContext;

extern WirelessContext *data_0217aa00;
extern void func_02053664(void);
extern int StructWM_SomeFn(StructWM *work, int callback, u32 dmaChannel);

void func_020536e0(void) {
    data_0217aa00->request = 1;
    data_0217aa00->busy = 1;

    if (StructWM_SomeFn(data_0217aa00->work, (int)func_02053664, 2) != 2) {
        data_0217aa00->busy = 0;
    }
}
