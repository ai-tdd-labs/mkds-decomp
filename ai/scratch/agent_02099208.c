/*
 * PURPOSE: Applies a special-item visual/audio flag to a kart when the item's
 * state is 1, and returns the kart's original special-item id.
 *
 * Arguments:
 *   obj   - pointer to the kart/racer object being updated (flags at +2,
 *           a "done" dword at +0xcc, another flag dword at +0x78).
 *   race  - pointer to a race/mode-info struct; field +0x29c is the current
 *           race mode/course type.
 *   state - pointer to a byte holding the item's current state (1 = active).
 *   id    - pointer to the byte holding the special-item id to return.
 *
 * When state==1, this ORs in a couple of engine flag bits (one halfword
 * flag, and conditionally a dword flag for race modes 1 and 3), marks the
 * kart's item processing as done, and calls func_020d26f8 (probably an
 * item-effect trigger). The original item id (*id) is always returned.
 */

extern void func_020d26f8(void);

extern unsigned short data_02156590;
extern unsigned int data_02156594;

struct Racer02099208 {
    unsigned char pad_0[2];
    unsigned short flags2;      /* +0x2 */
    unsigned char pad_4[0x78 - 4];
    unsigned int flags78;       /* +0x78 */
    unsigned char pad_7c[0xcc - 0x7c];
    unsigned int done;          /* +0xcc */
};

struct RaceInfo02099208 {
    unsigned char pad_0[0x29c];
    unsigned int mode;          /* +0x29c */
};

unsigned char func_02099208(struct Racer02099208 *obj, struct RaceInfo02099208 *race,
                             unsigned char *state, unsigned char *id)
{
    unsigned int mode;
    unsigned char idVal = *id;

    if (*state == 1) {
        obj->flags2 |= data_02156590;
        obj->done = 1;

        mode = race->mode;
        if (mode == 1 || mode == 3) {
            obj->flags78 |= data_02156594;
        }

        func_020d26f8();
    }

    return idVal;
}
