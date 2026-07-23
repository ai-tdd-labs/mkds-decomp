// PURPOSE: Reads one save-data chunk and sends it to the save loader.
// The second argument is probably remembered in shared save state.
// The remaining arguments are forwarded with a fixed flag value of one.
// The final stack argument is probably the chunk's destination or context.

typedef struct SaveWork {
    unsigned char _00[0x18];
    int value_18;
} SaveWork;

extern SaveWork *data_021759d4;
extern void func_0204b714(int, int, int, int, int, int);

void ReadSaveChunkImpl_from_thumb(int a, int b, int c, int d, int e, int f)
{
    data_021759d4->value_18 = b;
    func_0204b714(a, c, d, e, 1, f);
}
