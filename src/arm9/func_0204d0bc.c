// PURPOSE: Initializes an output block and reduces the owner's pending count.
// The first argument is probably an owner object containing two embedded blocks.
// The second argument receives initialized data and has its field at offset 0x80 cleared.
// The helper copies or prepares the owner's block at 0x46c8 from the block at 0x46c0.

typedef struct {
    unsigned char pad[0x80];
    int field_80;
} OutputBlock;

typedef struct {
    unsigned char pad[0x46c0];
    unsigned char block_46c0;
    unsigned char pad_46c1[7];
    unsigned char block_46c8;
    unsigned char pad_46c9[0x1b];
    int pending_count;
} OwnerBlock;

extern void func_0204d110(void *destination, void *source, OutputBlock *output);

void func_0204d0bc(OwnerBlock *owner, OutputBlock *output)
{
    func_0204d110(&owner->block_46c8, &owner->block_46c0, output);
    output->field_80 = 0;
    owner->pending_count--;
}
