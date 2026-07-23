// PURPOSE: Reads ROM data from the game card into the requested destination.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct CardRomRequest {
    void (*readFunc)(struct CardRomRequest *);
    u32 control;
    u8 *cachePage;
    u32 unused0c[5];
    u8 cacheBuffer[0x200];
} CardRomRequest;

typedef struct CardState {
    u8 unused00[0x1c];
    u32 romAddress;
    u32 destination;
    u32 remainingBytes;
} CardState;

extern CardState data_0217fa40;
extern void Card_WriteRomOperation(u32 command0, u32 command1);
extern int GlobalSZ_SomeFn(CardRomRequest *request);

static inline int Card_OnReadPageDirect(CardRomRequest *request)
{
#pragma unused(request)
    CardState *const state = &data_0217fa40;

    state->romAddress += 0x200;
    state->destination += 0x200;
    state->remainingBytes -= 0x200;
    return state->remainingBytes > 0;
}

void Card_DefaultRomAccess(CardRomRequest *request)
{
    CardState *const state = &data_0217fa40;

    while (1) {
        const u32 length = 0x200;
        u32 source = state->romAddress & (u32)-0x200;
        u32 destination;

        if ((source != state->romAddress) ||
            ((state->destination & 3) != 0) ||
            (state->remainingBytes < length)) {
            destination = (u32)request->cacheBuffer;
            request->cachePage = (u8 *)source;
        } else {
            destination = state->destination;
        }

        Card_WriteRomOperation((source >> 8) | 0xb7000000, source << 24);

        {
            u32 position = 0;

            *(volatile u32 *)0x040001a4 = request->control;
            while (1) {
                const u32 control = *(volatile u32 *)0x040001a4;

                if ((control & 0x00800000) != 0) {
                    u32 data = *(volatile u32 *)0x04100010;

                    if (position < length) {
                        ((u32 *)destination)[position++] = data;
                    }
                }
                if ((control & 0x80000000) == 0) {
                    break;
                }
            }
        }

        if (destination == state->destination) {
            if (!Card_OnReadPageDirect(request)) {
                break;
            }
        } else {
            if (!GlobalSZ_SomeFn(request)) {
                break;
            }
        }
    }
}
