// PURPOSE: Applies the requested wireless setting once the shared context is ready.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct UnkStruct_0217aa00 {
    int state;
    u8 pad_004[0x454 - 4];
    u16 flags;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void func_0204bcb4(void *value);

void func_0204f8a0(void *value)
{
    UnkStruct_0217aa00 *context = data_0217aa00;
    int enabled = 0;

    if ((context->flags & 0x40) != 0) {
        int state = (context == 0) ? 0 : context->state;
        int ready = 1;

        if (state != 1) {
            if (*(volatile u16 *)0x027ffc40 != 2) {
                ready = 0;
            }
        }
        if (ready != 0) {
            enabled = 1;
        }
    }

    if (enabled == 0) {
        return;
    }

    if (((context == 0) ? 0 : context->state) != 1) {
        return;
    }

    func_0204bcb4(value);
}
