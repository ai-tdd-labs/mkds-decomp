/* PURPOSE: Counts ten record values and creates a counted allocation.
 * The global record pointer supplies records selected by a fixed index table.
 * Each selected record contributes its value at offset 0xc to the total.
 * The result is probably used as the item count for the allocation helper.
 */

typedef struct Record020ca3e4 {
    int value;
    unsigned char padding[0xa8 - 4];
} Record020ca3e4;

typedef struct CountedHeapAllocation CountedHeapAllocation;

extern Record020ca3e4 *data_0217bc34;
extern unsigned int data_021696c0[];
extern CountedHeapAllocation **data_0217b42c;
extern int func_020c0ba8(CountedHeapAllocation **output, unsigned int count);

void func_020ca3e4(void)
{
    int index;
    int total;

    total = 0;
    for (index = 0; index < 10; index++) {
        total += data_0217bc34[data_021696c0[index]].value;
    }

    func_020c0ba8(data_0217b42c, total);
}
