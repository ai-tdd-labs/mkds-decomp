// PURPOSE: Sends a command after reserving the shared system state.
// The three arguments provide a command byte and two associated values.
// The shared state probably records the values for the receiving system.

typedef struct {
    int state;
    int value1;
    int value2;
} SharedState;

extern SharedState data_02180448;

extern int func_021501d8(void);
extern void func_0214fa7c(unsigned int word);

int func_0214f6bc(int command, int value1, int value2)
{
    if (func_021501d8() == 0) {
        return 1;
    }

    data_02180448.value1 = value1;
    data_02180448.value2 = value2;
    func_0214fa7c((command & 0xff) | 0x03006600);
    return 0;
}
