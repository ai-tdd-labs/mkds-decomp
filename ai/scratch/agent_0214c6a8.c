// PURPOSE: Copies the selected values into shared control slots.
// The selected entry is probably chosen by the current race state.
// Its three halfword values are converted to 20.12 fixed-point values.

typedef unsigned short u16;
typedef int s32;

typedef struct ValueColumn {
    u16 value;
    char padding[4];
} ValueColumn;

extern s32 func_02149004(void);
extern ValueColumn data_021616cc[];
extern ValueColumn data_021616ce[];
extern ValueColumn data_021616d0[];
extern s32 data_021802fc;
extern s32 data_021802ec;
extern s32 data_02180300;
extern s32 data_02180304;

void func_0214c6a8(void)
{
    s32 index = func_02149004();
    s32 first = (s32)data_021616cc[index].value << 12;
    s32 second = (s32)data_021616ce[index].value << 12;
    s32 third = (s32)data_021616d0[index].value << 12;

    data_021802fc = index;
    data_021802ec = first;
    data_02180300 = second;
    data_02180304 = third;
}
