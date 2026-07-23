// PURPOSE: Chooses the next available network slot.
typedef unsigned short u16;

typedef struct SlotState {
    unsigned char unknown_00[4];
    u16 slot;
} SlotState;

extern int func_02143280(void);

int func_0200ada4(SlotState *state)
{
    u16 slot;
    u16 count;
    u16 oldSlot;
    int available;

    available = func_02143280();
    if (available == 0) {
        return 0;
    }

    count = 0;
    oldSlot = state->slot;
    slot = oldSlot;
    do {
        if ((available & (1 << (slot - 1))) != 0 && oldSlot != slot) {
            state->slot = slot;
            break;
        }

        count++;
        {
            int next;
            if (slot == 16) {
                next = 1;
            } else {
                next = slot + 1;
            }
            slot = (u16)next;
        }
    } while (count < 16);

    return 1;
}
