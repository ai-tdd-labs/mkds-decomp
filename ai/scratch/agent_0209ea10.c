/*
PURPOSE: Marks a race entry's slot as processed (state 0xb) and returns its kind,
after possibly applying a driver flag and running an update callback the first time.
Arguments: obj is the owning manager (its per-entry array lives at +0x1000, stride
0x1000 indexed by entry->idx, state stored at +0x9c4); entry is the race entry
(idx at +0x74, mode at +0x29c); kindPtr points to a single kind byte. The second
argument to func_020d26f8 is entry itself. Probably part of per-frame driver
state bookkeeping.
*/

extern void func_020d26f8(void *obj, void *entry);
extern int data_021565e8;

int func_0209ea10(void *obj, void *entry, void *unused, unsigned char *kindPtr)
{
    unsigned short idx = *(unsigned short *)((char *)entry + 0x74);
    unsigned char kind = *kindPtr;
    void *slot = (char *)obj + (idx << 2) + 0x1000;

    if (*(int *)((char *)slot + 0x9c4) == 0) {
        int mode = *(int *)((char *)entry + 0x29c);
        if (mode == 1 || mode == 3) {
            *(int *)((char *)obj + 0x78) |= data_021565e8;
        }
        func_020d26f8(obj, entry);
    }

    idx = *(unsigned short *)((char *)entry + 0x74);
    slot = (char *)obj + (idx << 2) + 0x1000;
    *(int *)((char *)slot + 0x9c4) = 0xb;

    return kind;
}
