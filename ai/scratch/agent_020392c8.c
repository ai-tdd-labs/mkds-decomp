// PURPOSE: Packs selected flags into the scrolling state and advances it.
/* The input is written as a byte when the step is one, using the configured
 * flag mask to select and compact bits; otherwise it is stored as a halfword.
 * The state is then updated by the existing scrolling helper.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ScrollState {
    u32 start;
    u32 end;
    u32 alternateStart;
    u32 reverseStart;
    u32 unused10;
    u32 step;
    u16 flags;
} ScrollState;

extern ScrollState data_021755c0;
extern void func_02039378(int index, int mode);

void func_020392c8(u16 value)
{
    u32 step;
    u32 position;
    u32 end;

    step = data_021755c0.step;
    position = data_021755c0.alternateStart;
    end = data_021755c0.end;
    if (position + step > end) {
        return;
    }

    if (step == 1) {
        u16 flags = data_021755c0.flags;
        u32 bit = 1;
        u8 packed = 0;
        u8 output = 1;

        do {
            if (flags & (u16)bit) {
                if (value & (u16)bit) {
                    packed |= output;
                }
                output = (u8)(output << 1);
                if (output == 0) {
                    break;
                }
            }
            bit <<= 1;
        } while (bit < 0x10000);
        *(u8 *)&data_021755c0.alternateStart = packed;
    } else {
        *(u16 *)&data_021755c0.alternateStart = value;
    }
    func_02039378(1, 1);
}
