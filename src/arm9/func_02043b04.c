// PURPOSE: Resets each entry in the global CY object list.
// The list contains ten fixed-size objects.
// Each object is passed to its dedicated reset routine.

typedef struct StructCY {
    char bytes[0x5C];
} StructCY;

extern StructCY data_02175628[];
extern void StructCY_SomeFn_1(StructCY *object);

void func_02043b04(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        StructCY_SomeFn_1(&data_02175628[i]);
    }
}
