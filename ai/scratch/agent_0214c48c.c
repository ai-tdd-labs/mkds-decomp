// PURPOSE: Updates the display value from the current system state.
// The helper probably returns a state value used by the display hardware.
// Its raw value and a table-derived setting are saved in global memory.

extern int data_021802f4;
extern unsigned short data_021616bc[];
extern int data_021802f0;
extern int func_02148ff0(void);

void func_0214c48c(void) {
    int value = func_02148ff0();

    data_021802f4 = value;
    data_021802f0 = data_021616bc[value >> 4] << 12;
}
