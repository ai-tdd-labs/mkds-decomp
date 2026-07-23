// PURPOSE: Returns the adjusted total remainder when divided by seven.
//
// Reads two probably related counters from the current global work object.
// Their sum plus one is reduced modulo seven.

typedef struct WorkState {
    char _00[0x3C];
    int value_3C;
    char _40[4];
    int value_44;
} WorkState;

extern WorkState *data_02174e48;

int func_0202edfc(void)
{
    return (data_02174e48->value_3C + data_02174e48->value_44 + 1) % 7;
}
