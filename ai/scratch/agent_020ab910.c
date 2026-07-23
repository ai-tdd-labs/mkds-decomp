// PURPOSE: Updates the keyboard key range values.
// Stores four supplied values in the shared keyboard workspace.
// It then creates a sub-object from the two base values and the new range.

typedef unsigned int u32;

typedef struct Global78 {
    unsigned char pad_00[0x50];
    u32 keyValue0;
    u32 keyValue1;
    u32 keyValue2;
    u32 keyValue3;
    u32 keyValue4;
    u32 keyValue5;
} Global78;

extern Global78 *data_0217b334;
extern void func_020a9efc(void *arg1, void *arg2, void *arg3, void *arg4);

void func_020ab910(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
    data_0217b334->keyValue2 = arg0;
    data_0217b334->keyValue3 = arg1;
    data_0217b334->keyValue4 = arg2;
    data_0217b334->keyValue5 = arg3;
    func_020a9efc((void *)(data_0217b334->keyValue0 + data_0217b334->keyValue2),
                  (void *)(data_0217b334->keyValue1 + data_0217b334->keyValue3),
                  (void *)(data_0217b334->keyValue0 + data_0217b334->keyValue4),
                  (void *)(data_0217b334->keyValue1 + data_0217b334->keyValue5));
}
