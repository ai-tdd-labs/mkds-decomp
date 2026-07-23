// Syncs one 0x590-sized per-player entry (in the array at *data_0216fc40+0x10)
// with the current shared state in *data_0216fc3c (probably touch/input or
// network mirror state). If the entry's frame byte (+0x4B4) is one behind the
// shared counter (+6), only the slots flagged in the shared bitmask (+0xE) are
// cleared; if it is further behind, all 15 0x16-byte slots are wiped. Then the
// header fields and up-to-4 fresh source slots are copied in.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 lo : 4;     // low nibble, unused here
    u8 hi : 4;     // 1-based destination slot index, 0 = empty
    u8 rest[0x15];
} SrcSlot; // 0x16 bytes

typedef struct {
    u8 unk0[6];
    u8 unk6;            // frame/sequence counter
    u8 unk7[3];
    u8 unkA;
    u8 unkB;
    u16 unkC;
    u16 unkE;           // dirty bitmask (bit n+1 = slot n)
    SrcSlot slots[4];   // 0x10
    u8 unk68[8];        // 0x68
} SrcState;

typedef struct {
    u8 unk0[0x358];
    u8 unk358;
    u8 unk359;
    u16 unk35A;
    u16 unk35C;
    u8 slots[15][0x16]; // 0x35E .. 0x4A8
    u8 unk4A8[8];
    u8 unk4B0[4];
    u8 unk4B4;          // last-seen frame counter
    u8 unk4B5[0xD3];
    u16 unk588;         // valid-slot bitmask (bit 0 = header valid)
    u8 unk58A[6];
} Entry; // 0x590 bytes

typedef struct {
    u8 unk0[4];
    u16 unk4;           // per-player pending bitmask
    u8 unk6[0xA];
    Entry entries[1];   // 0x10
} EntryPool;

extern EntryPool *data_0216fc40;
extern SrcState *data_0216fc3c;

extern void Mem_CpuFill16(u16 value, void *dest, u32 size);
extern void CopyMemory16(const void *src, void *dest, u32 size);

void func_02008aa0(int slot)
{
    Entry *entry;
    volatile u16 fillA; // volatile: forces the strh/ldrh through sp+4
    volatile u16 fillB; // second fill temp at sp+6

    entry = &data_0216fc40->entries[slot];
    if (entry->unk4B4 != data_0216fc3c->unk6) {
        if ((u8)(entry->unk4B4 + 1) == data_0216fc3c->unk6) {
            // one frame behind: clear only the dirty slots
            int i;
            for (i = 0; i < 15; i++) {
                if (data_0216fc3c->unkE & (2 << i)) {
                    fillA = 0;
                    Mem_CpuFill16(fillA, entry->slots[i], 0x16);
                }
            }
            entry->unk588 &= ~data_0216fc3c->unkE;
            data_0216fc40->unk4 &= ~(1 << slot);
        } else {
            // too far behind: wipe all 15 slots
            fillB = 0;
            Mem_CpuFill16(fillB, entry->slots[0], 0x14A);
            entry->unk588 = 0;
            data_0216fc40->unk4 &= ~(1 << slot);
        }
        entry->unk4B4 = data_0216fc3c->unk6;
    } else {
        if (entry->unk588 == data_0216fc3c->unkC) {
            return; // already up to date
        }
    }

    // copy header fields and fresh source slots in
    entry->unk358 = data_0216fc3c->unkA;
    entry->unk35A = data_0216fc3c->unkC;
    entry->unk35C = data_0216fc3c->unkE;
    entry->unk588 |= 1;
    {
        int i;
        u32 j;
        for (i = 0; i < 8; i++) {
            entry->unk4A8[i] = data_0216fc3c->unk68[i];
        }
        for (j = 0; j < 4; j++) {
            u32 n = data_0216fc3c->slots[j].hi;
            if (n != 0) {
                CopyMemory16(&data_0216fc3c->slots[j], entry->slots[n - 1], 0x16);
                entry->unk588 |= 1 << n;
            }
        }
    }
}
