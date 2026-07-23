// PURPOSE: Gets a value from an object's active table.
typedef struct {
    unsigned char pad00[0x2D];
    unsigned char hasTable;
    unsigned char pad2E[0x0E];
    unsigned char tableRow;
} Object0212C400;

extern short func_02021868(int row, int index);

int func_0212c400(Object0212C400 **objectRef, int index, short *output)
{
    Object0212C400 *object;

    object = *objectRef;
    if (object == 0) {
        return 0;
    }

    if (object->hasTable == 0) {
        *output = object->hasTable == 0 ? 0 : -1;
        return 1;
    }

    *output = func_02021868(object->tableRow, index);
    return 1;
}
