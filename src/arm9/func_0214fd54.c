// PURPOSE: Sends a two-word command after reserving shared state.
// The command and flags provide the two command words.
// The two values are probably retained by the receiving system.

typedef struct SharedState {
    int state;
    int value1;
    int value2;
} SharedState;

extern SharedState data_02180448;

extern int func_021501d8(void);
extern void func_0214fa7c(unsigned int word);

int func_0214fd54(unsigned int command, unsigned int flags, int value1, int value2)
{
    if (func_021501d8() == 0) {
        return 1;
    }

    data_02180448.value1 = value1;
    data_02180448.value2 = value2;
    func_0214fa7c((command & 0xff) | 0x02006400);
    func_0214fa7c((flags & 0xffff) | 0x01010000);
    return 0;
}
