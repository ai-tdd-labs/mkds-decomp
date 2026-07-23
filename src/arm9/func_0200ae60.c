// PURPOSE: Registers a callback in the first free slot of a small table.
// The table starts at owner+0x30 and contains four-word entries.
// Interrupts are disabled while the table is searched and updated.

extern int Os_DisableIrq(void);
extern void Os_RestoreIrq(int state);
extern void Os_Terminate(void);

void func_0200ae60(void *owner, int value0, int value1, int value2, int value3)
{
    int *entry;
    int irq;

    irq = Os_DisableIrq();
    entry = (int *)((char *)owner + 0x30);

    for (;;) {
        if (entry >= (int *)((char *)owner + 0x70))
            Os_Terminate();
        if (entry[3] == 0) {
            entry[0] = value0;
            entry[1] = value1;
            entry[2] = value2;
            entry[3] = value3;
            break;
        }
        entry += 4;
    }

    Os_RestoreIrq(irq);
}
