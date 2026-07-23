// PURPOSE: Initializes the binary state and clears its shared working buffers.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct UnkStruct_0217aa00 {
    u8 _0000[0x165c];
    void *bufferA;
    u32 bufferASize;
    u8 _1664[4];
    void *bufferB;
} UnkStruct_0217aa00;

typedef struct StructBin {
    u8 _0000[0x14];
    u32 entries[8];
    u8 _0034[4];
    u16 unk38;
    u16 unk3a;
    u8 unk3c;
    u8 unk3d;
    u8 unk3e;
    u8 unk3f;
    u8 unk40;
    u8 unk41;
    u8 unk42;
    u8 _0043;
    u32 unk44;
} StructBin;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);

void StructBin_SomeFn_from_thumb(StructBin *bin)
{
    int i;

    if (data_0217aa00->bufferA != 0) {
        Mem_CpuFill8(data_0217aa00->bufferA, 0, data_0217aa00->bufferASize);
    }

    if (data_0217aa00->bufferB != 0) {
        Mem_CpuFill8(data_0217aa00->bufferB, 0, 0x4c0);
    }

    for (i = 0; i < 8; i++) {
        bin->entries[i] = i;
    }

    bin->unk3c = 7;
    bin->unk3d = 7;
    bin->unk3e = 7;
    bin->unk3f = 7;
    bin->unk40 = 7;
    bin->unk41 = 7;
    bin->unk38 = 7;
    bin->unk3a = 7;
    bin->unk42 = 0xff;
    bin->unk44 = 7;
}
