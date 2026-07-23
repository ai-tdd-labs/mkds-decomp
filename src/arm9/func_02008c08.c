/* PURPOSE: Copies the shared state's pending data block into one player's entry
 * and marks that block as received.
 *
 * idx selects the 0x590-sized entry in the pool at *data_0216fc40 (+0x10).
 * If the entry already saw this frame and the shared block (bit = shared +0xA)
 * is already applied (entry +0x580), nothing happens. Otherwise the block is
 * copied to region 0 (entry+0) or region 1 (entry+0x220) — chosen by the low
 * 2 bits of shared +0x4 — at block index (+0xA) * 0x62, bounds-checked against
 * entry+0x358. On success the region id, the applied-block bitmask and a
 * (1 << count)-1 valid mask (+0x584) are updated. Probably network/wireless
 * data reassembly.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unk0[4];
    u8 region : 2;      // 0x4: low 2 bits select destination region
    u8 frame;           // 0x5: frame/sequence counter
    u8 unk6[4];
    u8 blockIdx;        // 0xA: block index within the region
    u8 blockCount;      // 0xB: total block count
    u8 blockLen;        // 0xC: byte length of the pending block
    u8 unkD;
    u8 data[0x62];      // 0xE: pending payload
} SrcState;

typedef struct {
    u8 region0[0x220];  // 0x000: destination region 0
    u8 region1[0x138];  // 0x220: destination region 1 (ends at 0x358)
    u8 unk358[0x15a];
    u8 lastRegion;      // 0x4B2: region of the last applied block
    u8 lastFrame;       // 0x4B3: last-seen frame counter
    u8 unk4B4[0xCC];
    u32 doneMask;       // 0x580: bitmask of applied blocks
    u32 validMask;      // 0x584: (1 << blockCount) - 1
    u8 unk588[8];
} Entry; // 0x590 bytes

typedef struct {
    u8 unk0[0x10];
    Entry entries[1];   // 0x10
} EntryPool;

extern EntryPool *data_0216fc40;
extern SrcState *data_0216fc3c;

extern void CopyMemory16(const void *src, void *dest, u32 size);

void func_02008c08(int idx)
{
    Entry *entry = &data_0216fc40->entries[idx];
    u8 *end = (u8 *)entry + 0x358;      // copy must not run past region 1
    SrcState *s = data_0216fc3c;
    u8 *dst;

    if (entry->lastFrame == s->frame) {
        if (entry->doneMask & (1 << s->blockIdx)) {
            return; // block already applied this frame
        }
    }

    if (s->region == 0) {
        dst = (u8 *)entry;
    } else {
        dst = (u8 *)entry + 0x220;
    }
    dst += data_0216fc3c->blockIdx * 0x62; // ROM reloads the shared ptr here
    if (dst + data_0216fc3c->blockLen > end) {
        return; // would overflow the destination region
    }

    CopyMemory16(s->data, dst, data_0216fc3c->blockLen);

    entry->lastRegion = data_0216fc3c->region;
    entry->doneMask |= 1 << data_0216fc3c->blockIdx;
    entry->validMask = (1 << data_0216fc3c->blockCount) - 1;
}
