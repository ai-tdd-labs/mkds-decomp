/* Decodes one animation transform record into the destination's 3x3 matrix.
 * Compact records either mark the destination, copy eight signed values, or
 * probably build an axis-mapped rotation/scale matrix from two parameters. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct AnimContext {
    u8 *recordSelector;
    u8 pad04[0xd0];
    u8 *recordData;
} AnimContext;

typedef struct AnimOutput {
    u32 flags;
    u8 pad04[0x24];
    int matrix[9];
} AnimOutput;

extern AnimContext *data_02170500;
typedef struct MapColumn {
    u8 value;
    u8 pad[3];
} MapColumn;
extern MapColumn data_02152c30[];
extern MapColumn data_02152c31[];
extern MapColumn data_02152c32[];
extern MapColumn data_02152c33[];
extern void func_0214d32c(void *dst);

void func_02015044(AnimOutput *out)
{
    int first;
    int second;
    int axis;
    u8 *record;
    u8 *base = data_02170500->recordData;
    u8 *selector = data_02170500->recordSelector;
    u16 tableOffset = *(u16 *)(base + 6);
    u16 stride = *(u16 *)(base + tableOffset);
    u8 *entry = base + tableOffset + stride * selector[1];
    u32 recordOffset = *(u32 *)(entry + 4);
    s16 *values;

    record = base + recordOffset;
    values = (s16 *)(record + 4);

    if ((*(u16 *)record & 1) == 0) {
        values += 6;
    }

    if ((*(u16 *)record & 2) == 0) {
        if (*(u16 *)record & 8) {
            axis = (*(u16 *)record & 0xf0) >> 4;
            first = values[0];
            second = values[1];

            func_0214d32c(out->matrix);
            out->matrix[axis] = (*(u16 *)record & 0x100) ? -0x1000 : 0x1000;
            out->matrix[data_02152c30[axis].value] = first;
            out->matrix[data_02152c31[axis].value] = second;
            if (*(u16 *)record & 0x200) {
                second = -second;
            }
            out->matrix[data_02152c32[axis].value] = second;
            if (*(u16 *)record & 0x400) {
                first = -first;
            }
            out->matrix[data_02152c33[axis].value] = first;
            return;
        }

        out->matrix[0] = *(s16 *)(record + 2);
        out->matrix[1] = values[0];
        out->matrix[2] = values[1];
        out->matrix[3] = values[2];
        out->matrix[4] = values[3];
        out->matrix[5] = values[4];
        out->matrix[6] = values[5];
        out->matrix[7] = values[6];
        out->matrix[8] = values[7];
        return;
    }

    out->flags |= 2;
}
