// PURPOSE: Starts a pending extra file operation when the handler is ready.
// The handler and operation selector probably come from the file-loading state machine.
// It rejects unavailable states, then begins the asynchronous read for a valid handler.
// Return values are state-machine results whose precise meanings are still uncertain.

typedef struct ExtraFileOperationState {
    unsigned char padding_00[0x0c];
    int state_0c;
} ExtraFileOperationState;

typedef struct ExtraFileOperationHandler {
    unsigned char padding_00[0x38];
    void *operation_38;
} ExtraFileOperationHandler;

extern ExtraFileOperationState data_02175ec0;
extern void SomeFileAsyncReadFunc(ExtraFileOperationHandler *handler);

int UnkStruct_ExtraFileOperationHandler_Unk(ExtraFileOperationHandler *handler, int operation)
{
    switch (operation) {
    case 0:
        if (data_02175ec0.state_0c != 2) {
            return 5;
        }

        if (handler->operation_38 == 0) {
            return 0;
        }

        SomeFileAsyncReadFunc(handler);
        return 6;

    case 1:
        return 4;

    default:
        return 8;
    }
}
