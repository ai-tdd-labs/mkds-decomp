/* Generates the 16-character time-trial ghost code from a record.
 * Packs time (18 bits) / course id (5 bits) / character*37+kart (9 bits)
 * into a u32, appends 4 raw bytes from the record, computes a CRC over the
 * 10-byte block, XOR-obfuscates it backwards with a rolling key (seed 0xc3),
 * then emits 16 base-32 chars (5 bits each, MSB first) via the table
 * "S7LCX3JZE8FG4HBKWN52YPA6RTU9VMDQ". Returns 1 on success, 0 on failure. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* unsigned: table indexing must be ldrb, not ldrsb (-char signed) */
extern unsigned char data_0215494c[]; /* "S7LCX3JZE8FG4HBKWN52YPA6RTU9VMDQ" */

extern int GetCourseIdFromInternalId(int internalId);
extern void Mem_CpuCopy8(const void *src, void *dst, u32 size);
extern u16 CalculateCRCChecksum_from_thumb(void *data, u32 len, u32 mode);

/* Fields of the time-trial record actually read here (probably a ghost
 * header): 0x00 ms, 0x02 min, 0x03 sec, 0x04 4 raw bytes (probably part of
 * the MAC address / player id), 0x19 character, 0x1a kart. */
typedef struct TimeTrialRecord {
    u16 milliseconds;  /* 0x00 */
    u8 minutes;        /* 0x02 */
    u8 seconds;        /* 0x03 */
    u8 data4[4];       /* 0x04 */
    u8 unk8[0x11];     /* 0x08 */
    u8 character;      /* 0x19 */
    u8 kart;           /* 0x1a */
} TimeTrialRecord;

int GenerateTimeTrialCodeImpl(char *out, TimeTrialRecord *rec, int internalId) {
    u8 buf[10] = {0};
    u32 time;
    int courseId;
    u32 combo;
    u32 packed;
    int i;
    int c;
    u16 val;
    u8 j;
    int bitpos;
    u8 key;

    /* total time in milliseconds; must fit the 4-minute (18-bit) budget */
    time = rec->milliseconds + (rec->seconds * 1000 + rec->minutes * 60000);
    if (time >= 240000) {
        return 0; /* r0 still holds the 0 from the buffer init */
    }

    courseId = GetCourseIdFromInternalId(internalId);
    if (courseId < 0 || courseId >= 0x20) {
        return 0;
    }

    /* character/kart combination packed into 9 bits */
    combo = rec->kart + rec->character * 0x25;
    if (combo >= 0x200) {
        return 0;
    }

    packed = (time & 0x3ffff) << 14;
    packed = packed | ((courseId & 0x1f) << 9);
    packed = packed | (combo & 0x1ff);
    *(u32 *)&buf[0] = packed;
    Mem_CpuCopy8(rec->data4, buf + 4, 4);
    *(u16 *)&buf[8] = 0;
    CalculateCRCChecksum_from_thumb(buf, 10, 1);

    /* obfuscate back-to-front: each byte XORed with the (already encrypted)
     * byte that follows it in processing order, seeded with 0xc3 */
    key = 0xc3;
    for (c = 9; c >= 0; c--) {
        buf[c] = buf[c] ^ key;
        key = buf[c]; /* reload after the store, not the eor result */
    }

    /* emit 16 characters of 5 bits each, MSB first, from the 80-bit buffer.
     * c is reused as cursor/digit scratch: the ex-xor-counter web takes r2,
     * fresh i takes r5, fresh bitpos takes r3 — matching the ROM */
    for (i = 0, bitpos = 0; i < 16; i++) {
        val = 0;
        c = (u8)bitpos; /* u8 truncation of the bit cursor, hoisted */
        for (j = 0; j < 5; j++) {
            /* bi as int: keeps the &0xff on byteidx alive (range unknown) */
            int bi = (u8)(c + j);
            u8 byteidx = (u32)bi >> 3; /* u32 cast: lsr instead of asr */
            u8 shift = 7 - (bi % 8); /* signed modulo trick on int bi */
            val |= (buf[byteidx] >> shift) & 1;
            val <<= 1;
        }
        c = data_0215494c[(u8)((u32)val >> 1)]; /* u32 cast: lsr */
        out[i] = c;
        bitpos += 5;
    }
    return 1;
}
