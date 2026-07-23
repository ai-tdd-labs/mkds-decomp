/* PURPOSE: Marks a manager slot as "used" (value 0x1f) the first time a
 * check function reports it should activate, then returns a caller-supplied
 * flag byte unchanged.
 * arg0 = manager struct (has a u32 status field at +0x78 and an array of
 * per-slot int values starting at +0xd4), arg1 = state struct whose u16
 * field at +0x74 selects the slot index, arg2 = unused, arg3 = pointer to a
 * byte that is simply read and returned as-is.
 * If the selected slot is still 0 AND func_020d26f8(mgr, state) reports
 * nonzero, OR a global flag mask into mgr->f78 and set the slot to 0x1f. */

extern int func_020d26f8(void *mgr, void *state);

extern unsigned int data_02156470; /* u32 flag mask ORed into mgr->f78 */

struct Manager {
    char pad_000[0x78];
    unsigned int f78;       /* status flag bits */
    char pad_7c[0xd4 - 0x7c];
    int slot[1];             /* per-slot value array, indexed by state->f74 */
};

struct SlotState {
    char pad_000[0x74];
    unsigned short f74;      /* slot index into Manager::slot */
};

unsigned char func_02093754(struct Manager *mgr, struct SlotState *state,
                             int unused, unsigned char *flagPtr)
{
    unsigned char ret = *flagPtr;

    if (mgr->slot[state->f74] == 0 && func_020d26f8(mgr, state) != 0) {
        mgr->f78 |= data_02156470;
        mgr->slot[state->f74] = 0x1f;
    }

    return ret;
}
