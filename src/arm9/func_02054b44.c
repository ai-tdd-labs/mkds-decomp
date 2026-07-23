/* Status poll of the global object at data_0217aa00 (probably a network /
 * wifi or scene-transition context). Returns:
 *   3 - object is live (state set, unk4 != 13) but flag 0x80 clear and
 *       unk8 != 9 (probably an error/unexpected-mode condition),
 *   2 - unk1e3c set and the u16 handle at +0x432 is 0xFFFF (invalid),
 *   0 - busy (+0x10 nonzero) or no pending request,
 *   1 - state == 1, or after converting request 0x2a into 0x28/0x29
 *       depending on state (request forwarding). */
typedef unsigned short u16;

typedef struct UnkStruct_0217aa00 {
    int state;                        /* 0x000: 1/2 observed */
    int unk4;                         /* 0x004: compared with 13 */
    int unk8;                         /* 0x008: compared with 9 */
    int request;                      /* 0x00c: 0x28/0x29/0x2a */
    int busy;                         /* 0x010: nonzero -> return 0 */
    unsigned char pad14[0x432 - 0x14];
    u16 handle;                       /* 0x432: 0xFFFF = invalid */
    unsigned char pad434[0x454 - 0x434];
    u16 flags;                        /* 0x454: bit 0x80 tested */
    unsigned char pad456[0x1e3c - 0x456];
    int unk1e3c;                      /* 0x1e3c: gates the handle check */
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;

extern void func_0204f148(void);

int func_02054b44(void) {
    UnkStruct_0217aa00 *obj = data_0217aa00;
    int result = 0;
    int c4 = 0; /* ip in the ROM */
    int c3 = 0; /* r3 */
    int c2 = 0; /* r2 */
    int f0;
    u16 v;
    int s;

    /* three explicitly materialized flags: && would be copy-propagated */
    f0 = (obj == 0) ? 0 : obj->state; /* zero arm first: moveq before ldrne */
    if (f0 != 0) {
        if (obj->unk4 != 13) {
            c2 = 1;
        }
    }
    if (c2) {
        if ((obj->flags & 0x80) == 0) {
            c3 = 1;
        }
    }
    if (c3) {
        if (obj->unk8 != 9) {
            c4 = 1;
        }
    }
    if (c4) {
        return 3;
    }

    if (obj->unk1e3c != 0) {
        /* u16 assignment forces the lsl/lsr #16 truncation pair */
        v = (obj->state == 2) ? obj->handle : 0;
        if (v == 0xFFFF) { /* 0xFFFF comes from the literal pool */
            return 2;
        }
    }

    if (obj->busy != 0) {
        return 0;
    }

    /* null-check repeated on purpose: the ROM re-tests r0 each time */
    if (((obj == 0) ? 0 : obj->state) == 1) {
        return 1;
    }

    switch (obj->request) {
    case 0x28:
    case 0x29:
        func_0204f148();
        break;
    case 0x2a:
        s = (obj == 0) ? 0 : obj->state;
        /* inner switch, not if/else-if: case 1 body goes behind a branch,
         * case 2 becomes predicated moveq/streq right after the dispatch */
        switch (s) {
        case 1:
            obj->request = 0x28;
            break;
        case 2:
            obj->request = 0x29;
            break;
        }
        result = 1;
        break;
    }
    return result;
}
