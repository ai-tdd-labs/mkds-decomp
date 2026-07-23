// PURPOSE: Initializes the shared wireless callback state and terminates if callback registration fails.

typedef unsigned short u16;

typedef struct {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    int field_2c;
    u16 field_30;
} State0204c28c;

extern State0204c28c data_02175ec0;
extern int data_02175ea0;
extern void Fs_Initialize(int);
extern int func_0214358c(unsigned int, void *, void *);
extern void func_0204cc94(void);
extern void Os_Terminate(void);

void func_0204c28c(int arg0, int arg1, int arg2, int arg3)
{
    int a0 = arg0;
    int a1 = arg1;
    int a2 = arg2;
    int a3 = arg3;
    State0204c28c * const state = &data_02175ec0;

    Fs_Initialize(-1);
    state->field_30 = (u16)a0;
    state->field_04 = 0;
    state->field_08 = 0;
    state->field_0c = 0;
    state->field_10 = a1;
    state->field_14 = a2;
    state->field_18 = a3;
    state->field_1c = 0;
    state->field_24 = 0;
    state->field_20 = 0;
    state->field_28 = 0;
    state->field_2c = 14;
    data_02175ea0 = 0;
    if (func_0214358c((u16)a0, func_0204cc94, 0) != 0) {
        Os_Terminate();
    }
}
