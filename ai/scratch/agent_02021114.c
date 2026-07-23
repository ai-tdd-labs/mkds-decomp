/* PURPOSE: Returns the currently selected sound command-list value.
 * Takes no arguments. Interrupts are disabled while the function chooses
 * between two global values, then the previous interrupt state is restored.
 * The exact meaning of the selector and returned values is still uncertain. */

typedef unsigned int u32;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);

extern int data_021732cc;
extern int data_021732d0;
extern int data_021732e8;

int func_02021114(void) {
    u32 irqState = Os_DisableIrq();
    int selectedValue;

    if (data_021732d0 == 0) {
        selectedValue = data_021732cc;
    } else {
        selectedValue = data_021732e8;
    }

    Os_RestoreIrq(irqState);
    return selectedValue;
}
