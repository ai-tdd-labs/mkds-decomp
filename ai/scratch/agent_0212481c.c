// Copies the tile graphics of one metatile entry onto another: looks up the
// destination and source metatile entries in two cell banks, queues a VRAM
// transfer (TEQ cmd 0x13/0x23) per tile record, marks which destination
// palette slots were used and rewrites the palette bits of the source tile
// attributes, then queues palette-block transfers (cmd 0xe/0x1e) for every
// contiguous run of used palette slots. 'alt' probably selects main/sub engine.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TileRec {
    u16 f0;   // bits 14-15: group/quadrant selector (probably rotation)
    u16 f2;   // bits 14-15: flip flags
    u16 attr; // bits 0-9: tile index, bits 12-15: palette index
} TileRec;

typedef struct MetatileEntry {
    u16 count; // number of tile records
    u16 f2;
    TileRec *tiles;
} MetatileEntry;

typedef struct BankSlot { // 8-byte directory record; dir starts with one header record
    int f0;
    int f4; // low 16 bits: metatile entry id
} BankSlot;

typedef struct DestInfo {
    u8 pad[0x14];
    u8 *charBase; // +0x14: destination character (tile gfx) base
} DestInfo;

typedef struct PalInfo {
    u8 pad[0xc];
    u8 *palBase; // +0xc: destination palette base
} PalInfo;

extern MetatileEntry *CellBank_GetMetatileEntry(void *bank, u16 id);
extern void Arm_FlushRange(void *ptr, u32 size);
extern void AllocateReserveTEQSub(int cmd, u32 offset, void *dst, u32 size);
extern u8 data_0215d024[]; // tile-size lookup: [flip + quadrant*4] -> block count

void func_0212481c(int idxA, void *bankA, DestInfo *dest, PalInfo *pal,
                   BankSlot *dirA, int alt, int idxB, void *bankB, BankSlot *dirB)
{
    int count;           // sp+0x08
    u32 srcOff;          // sp+0x0c
    u8 *dst;             // sp+0x10
    MetatileEntry *entA; // sp+0x14
    int i;               // sp+0x18
    u8 used[16];         // sp+0x1c
    u32 attrA;           // r7
    MetatileEntry *entB; // r6
    int size;            // r5
    BankSlot *sa;
    BankSlot *sb;

    // slot 0 of each directory is a header; real slots start at +8
    sa = dirA + 1;
    entA = CellBank_GetMetatileEntry(bankA, (u16)sa[idxA].f4);
    sb = dirB + 1;
    entB = CellBank_GetMetatileEntry(bankB, (u16)sb[idxB].f4);
    count = entA->count;
    for (i = 0; i < 16; i++) {
        used[i] = 0;
    }
    for (i = 0; i < count; i++) {
        attrA = entA->tiles[i].attr;
        srcOff = (entB->tiles[i].attr & 0x3FF) << 5;
        // size table indexed by flip bits (f2 top 2) + quadrant (f0 top 2) * 4
        size = *(data_0215d024 + (((entA->tiles[i].f2 << 16) & 0xC0000000) >> 30) +
                (((entA->tiles[i].f0 & 0xC000u) >> 14) << 2)) << 5;
        // assignment inside the call arg keeps dst spilled while size stays in r5
        Arm_FlushRange(dst = dest->charBase + ((attrA & 0x3FF) << 5), size);
        if (alt == 0) {
            AllocateReserveTEQSub(0x13, srcOff, dst, size);
        } else {
            AllocateReserveTEQSub(0x23, srcOff, dst, size);
        }
        {
            u32 palIdx = (attrA & 0xF000u) >> 12;
            used[palIdx] = 1;
            entB->tiles[i].attr &= ~0xF000;
            entB->tiles[i].attr |= palIdx << 12;
        }
    }
    {
        int start = 0;
        int run = 0;
        // reuse i as the counter: a fresh counter would color r5/r4 swapped
        for (i = 0; i < 16; i++) {
            if (used[i] && start + run < 15) {
                run++;
            } else {
                if (run > 0) {
                    u32 off = start << 5;
                    u8 *pd = pal->palBase + off;
                    u32 len = run << 5;
                    if (alt == 0) {
                        AllocateReserveTEQSub(0xe, off, pd, len);
                    } else {
                        AllocateReserveTEQSub(0x1e, off, pd, len);
                    }
                    start = i + 1;
                    run = 0;
                } else {
                    start = i + 1;
                }
            }
        }
    }
}
