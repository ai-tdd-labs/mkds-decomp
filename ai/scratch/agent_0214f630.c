// PURPOSE: Updates the pending power-management request.
// The three arguments are saved for a probably asynchronous operation.
// It reports one when the request cannot start and zero after queuing it.

typedef struct PendingRequest {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
} PendingRequest;

extern PendingRequest data_02180448;
extern int func_021501d8(void *arg);
extern void func_0214fa7c(void *arg);

int func_0214f630(void *arg0, int arg1, int arg2)
{
    if (func_021501d8(arg0) == 0)
        return 1;

    data_02180448.unknown_04 = arg1;
    data_02180448.unknown_08 = arg2;
    data_02180448.unknown_0c = (int)arg0;
    func_0214fa7c(&data_02180448);
    return 0;
}
