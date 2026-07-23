/* PURPOSE: Updates the game's current button input.
 * Takes no arguments. It probably selects between a software-provided input
 * value and the Nintendo DS hardware keys, then records the selected state.
 * The exact meaning of the mode field at offset 0x24 is uncertain. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputState {
    u8 unknown_00[0x24];
    u32 useSoftwareInput;
} InputState;

extern InputState data_021755dc;
extern u16 GetSomeInput(void);
extern void StructG_UpdateInput(u16 buttons, InputState *inputState);

void UpdateInput(void)
{
    u16 buttons;

    if (data_021755dc.useSoftwareInput != 0) {
        buttons = GetSomeInput();
    } else {
        /* Both key sources are active-low; keep the DS's 14 input bits. */
        buttons = ((*(volatile u16 *)0x04000130 |
                    *(volatile u16 *)0x027fffa8) ^ 0x2fff) & 0x2fff;
    }

    StructG_UpdateInput(buttons, &data_021755dc);
}
