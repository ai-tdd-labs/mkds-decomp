/* PURPOSE: Initializes a mode object from a resource.
 * The first argument receives a cleared 0x54-byte mode object.
 * The second argument is saved as the mode's resource at offset 0x04.
 * Three global callback values are installed at offsets 0x0c, 0x14, and 0x1c.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*ModeCallback)(void);

typedef struct Mode {
    u32 unknown_00;
    void *resource;
    u32 unknown_08;
    ModeCallback callback_0c;
    u32 unknown_10;
    ModeCallback callback_14;
    u32 unknown_18;
    ModeCallback callback_1c;
    u8 unknown_20[0x34];
} Mode;

extern void MIi_CpuClear32(u32 value, void *destination, u32 size);
extern ModeCallback data_021617e8;
extern ModeCallback data_021617ec;
extern ModeCallback data_021617f0;

void Mode_CreateFromResource(Mode *mode, void *resource)
{
    volatile u32 clearValue = 0;

    MIi_CpuClear32(clearValue, mode, 0x54);
    mode->callback_0c = data_021617f0;
    mode->callback_14 = data_021617ec;
    mode->callback_1c = data_021617e8;
    mode->resource = resource;
}
